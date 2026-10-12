#include "common/aglUniformBlock.h"

#include "detail/aglGPUMemBlockMgr.h"
#include "driver/aglNVNMgr.h"

namespace agl {

#define ALIGN_FORWARD(value, align) (((value) + (align) - 1) & -(align))

static constexpr u32 cElementSize = sizeof(u32);

struct TypeInfo {
    u8 size = 0;
    u8 alignment = 0;
    u8 arrayStride = 0;
    u8 _3 = 0;
};

static constexpr TypeInfo createTypeInfo(size_t size, size_t align) {
    TypeInfo info;
    info.size = ALIGN_FORWARD(size, cElementSize) / cElementSize;
    info.alignment = align;
    // Array stride is aligned to 4 elements
    info.arrayStride = ALIGN_FORWARD(info.size, 4);
    return info;
}

static constexpr TypeInfo cTypeInfo[static_cast<size_t>(UniformBlock::Type::Max)] = {
    createTypeInfo(sizeof(bool), 1),
    createTypeInfo(sizeof(s32), 1),
    createTypeInfo(sizeof(u32), 1),
    createTypeInfo(sizeof(f32), 1),

    createTypeInfo(sizeof(sead::Vector2f), 2),
    createTypeInfo(sizeof(sead::Vector3f), 4),
    createTypeInfo(sizeof(sead::Vector4f), 4),
    createTypeInfo(sizeof(sead::Vector4i), 4),

    createTypeInfo(sizeof(sead::Vector4f) * 2, 8),
    createTypeInfo(sizeof(sead::Vector4f) * 2, 8),
    createTypeInfo(sizeof(sead::Vector4f) * 2, 8),

    createTypeInfo(sizeof(sead::Vector4f) * 3, 12),
    createTypeInfo(sizeof(sead::Vector4f) * 3, 12),
    createTypeInfo(sizeof(sead::Vector4f) * 3, 12),

    createTypeInfo(sizeof(sead::Vector4f) * 4, 16),
    createTypeInfo(sizeof(sead::Vector4f) * 4, 16),
    createTypeInfo(sizeof(sead::Vector4f) * 4, 16),

    createTypeInfo(1, 1),
};

UniformBlock::UniformBlock() = default;

UniformBlock::~UniformBlock() {
    destroy();
}

void UniformBlock::destroy() {
    if (mFlags.isOn(Flags::NvnBufferInitialized)) {
        nvnBufferFinalize(&mNvnBuffer);

        mFlags.reset(Flags::NvnBufferInitialized);
    }

    mBufferSize = 0;
    mCurrentBufferData = nullptr;
    mDataSize = 0;
    mBlockSize = 0;

    if (mFlags.isOn(Flags::HeaderAllocated)) {
        delete mHeader->members;
        delete mHeader;

        mFlags.reset(Flags::HeaderAllocated);
    }

    mHeader = nullptr;

    if (mFlags.isOn(Flags::BufferAllocated)) {
        mBuffer.destroy();

        mFlags.reset(Flags::BufferAllocated);
    }
}

void UniformBlock::startDeclare(s32 memberNum, sead::Heap* heap) {
    mHeader = new (heap) Header_;
    mHeader->members = new (heap) Member_[memberNum];
    mHeader->memberNum = memberNum;
    mHeader->declaredNum = 0;

    mFlags.set(Flags::HeaderAllocated);
    mDataSize = 0;
    mBlockSize = 0;
}

u8 UniformBlock::getStrideArray_(u8 type) const {
    return cTypeInfo[type].arrayStride;
}

void UniformBlock::declare_(Type type, s32 arraySize, size_t structSize, size_t structAlign) {
    Member_* member = &mHeader->members[mHeader->declaredNum];
    member->type = static_cast<u8>(type);
    member->arraySize = arraySize;

    u32 align;
    if (type == Type::Struct) {
        align = structAlign / cElementSize;
        member->stride = structSize / cElementSize;
    } else if (arraySize == 1) {
        align = cTypeInfo[member->type].alignment;
        member->stride = cTypeInfo[member->type].size;
    } else {
        align = member->stride = getStrideArray_(member->type);
    }

    mDataSize = ALIGN_FORWARD(mDataSize, align * cElementSize);
    member->offset = mDataSize;
    mDataSize += member->stride * cElementSize * member->arraySize;

    mHeader->declaredNum++;
    if (mHeader->declaredNum == mHeader->memberNum) {
        mDataSize = ALIGN_FORWARD(mDataSize, 32);
    }

    mBlockSize = ALIGN_FORWARD(mDataSize, getBlockAlignment_());
}

void UniformBlock::declare(const UniformBlock& other) {
    mHeader = other.mHeader;
    mDataSize = other.mDataSize;
    mBlockSize = other.mBlockSize;
    mFlags.reset(Flags::HeaderAllocated);
}

size_t UniformBlock::calcRequiredBufferSize(s32 bufferNum, s32 instanceNum) const {
    size_t blocks = mBlockSize * (instanceNum * bufferNum - 1);
    size_t last = ALIGN_FORWARD(mDataSize, getBlockAlignment_());
    return last + blocks;
}

void UniformBlock::create(sead::Heap* heap, s32 bufferNum, s32 instanceNum) {
    s32 size = calcRequiredBufferSize(bufferNum, instanceNum);
    GPUMemVoidAddr buffer =
        GPUMemVoidAddr::alloc(size, heap, getBlockAlignment_(), MemoryAttribute::_01);

    mFlags.set(Flags::BufferAllocated);
    setBuffer(buffer, bufferNum, instanceNum);
}

void UniformBlock::setBuffer(GPUMemVoidAddr buffer, s32 bufferNum, s32 instanceNum) {
    mBufferNum = bufferNum;
    mBuffer = GPUMemVoidAddr(buffer);
    mInstanceNum = instanceNum;

    if (mHeader) {
        mBufferSize = calcRequiredBufferSize(bufferNum, instanceNum);
    }

    if (mBuffer.isValid()) {
        if (mFlags.isOn(Flags::NvnBufferInitialized)) {
            nvnBufferFinalize(&mNvnBuffer);
        }

        NVNbufferBuilder builder;
        nvnBufferBuilderSetDevice(&builder, driver::NVNMgr::instance()->getNVNdevice());
        nvnBufferBuilderSetDefaults(&builder);
        nvnBufferBuilderSetStorage(&builder, mBuffer.getMemoryPool()->getDriverPool(),
                                   mBuffer.getByteOffset(), mBufferSize);
        nvnBufferInitialize(&mNvnBuffer, &builder);

        mFlags.set(Flags::NvnBufferInitialized);
    }

    mCurrentBufferIndex = 0;
    mCurrentBufferData = mBuffer.getData();
}

void UniformBlock::createWithBuffer(GPUMemVoidAddr buffer, s32 bufferNum, s32 instanceNum) {
    setBuffer(buffer, bufferNum, instanceNum);
}

void UniformBlock::createWithoutBuffer() {
    setBuffer(GPUMemVoidAddr(), 1, 1);
}

void UniformBlock::createDirect(GPUMemVoidAddr buffer, size_t size) {
    mDataSize = size;
    mBufferSize = size;

    setBuffer(buffer, 1, 1);
}

void UniformBlock::copyAllTo(UniformBlock* target, s32 bufferIndex, s32 instanceIndex) const {
    void* src = getDataPtr_(bufferIndex, instanceIndex);
    void* dst = target->getDataPtr_(bufferIndex, instanceIndex);

    sead::MemUtil::copy(dst, src, mDataSize);
}

void UniformBlock::copyPartialTo(UniformBlock* target, s32 firstSrcMember, s32 lastSrcMember,
                                 s32 firstDstMember, s32 lastDstMember, s32 bufferIndex,
                                 s32 instanceIndex) const {
    auto src = static_cast<const u8*>(getDataPtr_(bufferIndex, instanceIndex));
    const auto& srcFirst = mHeader->members[firstSrcMember];
    const auto& srcLast = mHeader->members[lastSrcMember];
    const u8* srcBegin = src + srcFirst.offset;
    const u8* srcEnd = src + srcLast.offset + srcLast.stride * cElementSize * srcLast.arraySize;
    s32 srcSize = srcEnd - srcBegin;

    auto dst = static_cast<u8*>(target->getDataPtr_(bufferIndex, instanceIndex));
    const auto& dstFirst = target->mHeader->members[firstDstMember];
    const auto& dstLast = target->mHeader->members[lastDstMember];
    u8* dstBegin = dst + dstFirst.offset;
    u8* dstEnd = dst + dstLast.offset + dstLast.stride * cElementSize * dstLast.arraySize;
    s32 dstSize = dstEnd - dstBegin;

    SEAD_ASSERT(srcSize == dstSize);

    sead::MemUtil::copy(dstBegin, srcBegin, srcSize);
}

void UniformBlock::fill(u32 value, s32 blockIndex) {
    auto dst =
        reinterpret_cast<u32*>(static_cast<u8*>(mCurrentBufferData) + mBlockSize * blockIndex);

    s32 elemNum = mDataSize / cElementSize;
    for (s32 i = 0; i < elemNum; i++) {
        dst[i] = value;
    }
}

void UniformBlock::writeMemory(u32* dst, const u32* src, s32 num, s32 dstStride, s32 srcStride,
                               const void*) {
    for (s32 i = 0; i < num; i++) {
        for (s32 j = 0; j < srcStride; j++) {
            dst[j] = *src++;
        }

        dst += dstStride;
    }
}

void UniformBlock::setData_(void* buffer, s32 index, const void* data, s32 arrayIndex,
                            s32 arrayNum) const {
    const auto& member = mHeader->members[index];
    u8 type = member.type;
    u8 elemStride = cTypeInfo[type].size;
    u8 arrayStride = getStrideArray_(type);

    auto dst =
        reinterpret_cast<u32*>(static_cast<u8*>(buffer) + member.offset) + arrayIndex * arrayStride;
    writeMemory(dst, static_cast<const u32*>(data), arrayNum, arrayStride, elemStride, nullptr);
}

void UniformBlock::setDataStruct_(void* buffer, s32 index, const void* data, s32 arrayIndex,
                                  s32 arrayNum, u32 structSize) const {
    verifyStructSize_(structSize);

    const auto& member = mHeader->members[index];
    s32 elemStride = structSize / sizeof(u32);
    s32 arrayStride = structSize / sizeof(u32);

    auto dst =
        reinterpret_cast<u32*>(static_cast<u8*>(buffer) + member.offset) + arrayIndex * arrayStride;
    writeMemory(dst, static_cast<const u32*>(data), arrayNum, arrayStride, elemStride, nullptr);
}

void UniformBlock::dcbz(s32 blockIndex) const {
    sead::MemUtil::fillZero(static_cast<u8*>(mCurrentBufferData) + mBlockSize * blockIndex,
                            mDataSize);
}

void UniformBlock::dcbz(u32, s32 blockIndex) const {
    sead::MemUtil::fillZero(static_cast<u8*>(mCurrentBufferData) + mBlockSize * blockIndex,
                            mDataSize);
}

}  // namespace agl