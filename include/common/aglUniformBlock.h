#pragma once

#include <nvn/nvn.h>
#include <nvn/nvn_FuncPtrInline.h>

#include <math/seadMatrix.h>
#include <math/seadVector.h>

#include "common/aglGPUMemAddr.h"
#include "common/aglShaderLocation.h"

namespace sead {
class Heap;
}  // namespace sead

namespace agl {

class DrawContext;
class ShaderLocation;

class UniformBlock {
public:
    enum class Type {
        Bool = 0,
        Int = 1,
        UInt = 2,
        Float = 3,
        Vec2 = 4,
        Vec3 = 5,
        Vec4 = 6,
        IVec4 = 7,
        Mat2x2 = 8,
        Mat2x3 = 9,
        Mat2x4 = 10,
        Mat3x2 = 11,
        Mat3x3 = 12,
        Mat3x4 = 13,
        Mat4x2 = 14,
        Mat4x3 = 15,
        Mat4x4 = 16,
        Struct = 17,
        Max = 18,
    };

    UniformBlock();
    virtual ~UniformBlock();

    void destroy();

    void startDeclare(s32 memberNum, sead::Heap* heap);
    void declare(const UniformBlock& other);

    void declare(Type type, s32 arraySize = 1) { declare_(type, arraySize, 0, 1); }
    template <typename T>
    void declareStruct(s32 arraySize = 1) {
        declare_(Type::Struct, arraySize, sizeof(T), alignof(T));
    }

    void setDataBool(s32 index, const bool* data, s32 arrayIndex = 0, s32 elementCount = 1) const {
        // Cannot pass bool directly, since its size is smaller than 4 bytes
        for (s32 i = 0; i < elementCount; i++) {
            s32 value = data[i];
            setDataInt(index, &value, arrayIndex + i);
        }
    }
    void setDataInt(s32 index, const s32* data, s32 arrayIndex = 0, s32 elementCount = 1) const {
        setData_(mCurrentBufferData, index, data, arrayIndex, elementCount);
    }
    void setDataUInt(s32 index, const u32* data, s32 arrayIndex = 0, s32 elementCount = 1) const {
        setData_(mCurrentBufferData, index, data, arrayIndex, elementCount);
    }
    void setDataFloat(s32 index, const f32* data, s32 arrayIndex = 0, s32 elementCount = 1) const {
        setData_(mCurrentBufferData, index, data, arrayIndex, elementCount);
    }
    void setDataVec2(s32 index, const sead::Vector2f* data, s32 arrayIndex = 0,
                     s32 elementCount = 1) const {
        setData_(mCurrentBufferData, index, data, arrayIndex, elementCount);
    }
    void setDataVec3(s32 index, const sead::Vector3f* data, s32 arrayIndex = 0,
                     s32 elementCount = 1) const {
        setData_(mCurrentBufferData, index, data, arrayIndex, elementCount);
    }
    void setDataVec4(s32 index, const sead::Vector4f* data, s32 arrayIndex = 0,
                     s32 elementCount = 1) const {
        setData_(mCurrentBufferData, index, data, arrayIndex, elementCount);
    }
    void setDataIVec4(s32 index, const sead::Vector4i* data, s32 arrayIndex = 0,
                      s32 elementCount = 1) const {
        setData_(mCurrentBufferData, index, data, arrayIndex, elementCount);
    }
    void setDataMat2x2(s32 index, const sead::Matrix22f* data, s32 arrayIndex = 0,
                       s32 elementCount = 1) const {
        setData_(mCurrentBufferData, index, data, arrayIndex, elementCount);
    }
    void setDataMat3x3(s32 index, const sead::Matrix33f* data, s32 arrayIndex = 0,
                       s32 elementCount = 1) const {
        setData_(mCurrentBufferData, index, data, arrayIndex, elementCount);
    }
    void setDataMat3x4(s32 index, const sead::Matrix34f* data, s32 arrayIndex = 0,
                       s32 elementCount = 1) const {
        setData_(mCurrentBufferData, index, data, arrayIndex, elementCount);
    }
    void setDataMat4x4(s32 index, const sead::Matrix44f* data, s32 arrayIndex = 0,
                       s32 elementCount = 1) const {
        setData_(mCurrentBufferData, index, data, arrayIndex, elementCount);
    }
    template <typename T>
    void setDataStruct(s32 index, const T* data, s32 arrayIndex, s32 elementCount) {
        setDataStruct_(mCurrentBufferData, index, reinterpret_cast<const void*>(&data), arrayIndex,
                       elementCount, sizeof(T));
    }

    size_t calcRequiredBufferSize(s32 bufferNum, s32 instanceNum) const;
    void create(sead::Heap* heap, s32 bufferNum, s32 instanceNum);
    void setBuffer(GPUMemVoidAddr buffer, s32 bufferNum, s32 instanceNum);

    void createWithBuffer(GPUMemVoidAddr buffer, s32 bufferNum, s32 instanceNum);
    void createWithoutBuffer();
    void createDirect(GPUMemVoidAddr buffer, size_t size);

    void copyAllTo(UniformBlock* target, s32 bufferIndex, s32 instanceIndex) const;
    void copyPartialTo(UniformBlock* target, s32, s32, s32, s32, s32, s32) const;

    void fill(u32 value, s32 blockIndex);
    static void writeMemory(u32* dst, const u32* src, s32 num, s32 dstStride, s32 srcStride,
                            const void*);

    void dcbz(s32 blockIndex) const;
    void dcbz(u32, s32 blockIndex) const;

    virtual void invalidateGPUCache(DrawContext* context, s32 blockIndex) const {}

    bool setUniform(DrawContext* context, const NVNbufferAddress& address,
                    const ShaderLocation& location, u32 offset, size_t size) const;

    bool activate(DrawContext* context, const UniformBlockLocation& location,
                  s32 instanceIndex = 0) {
        NVNbufferAddress address =
            nvnBufferGetAddress(&mNvnBuffer) +
            (mCurrentBufferIndex * mInstanceNum + instanceIndex) * mBlockSize;
        return setUniform(context, address, location, 0, mBlockSize);
    }

protected:
    void* getDataPtr_(s32 bufferIndex, s32 instanceIndex) const {
        if (bufferIndex == -1) {
            bufferIndex = mCurrentBufferIndex;
        }

        return GPUMemVoidAddr(mBuffer, (bufferIndex * mInstanceNum + instanceIndex) * mBlockSize)
            .getData();
    }

    void declare_(Type type, s32 arraySize, size_t structSize, size_t structAlign);

    void setData_(void* buffer, s32 index, const void* data, s32 arrayIndex, s32 arrayNum) const;
    void setDataStruct_(void* buffer, s32 index, const void* data, s32 arrayIndex, s32 arrayNum,
                        u32 structSize) const;

    virtual u8 getStrideArray_(u8 type) const;
    virtual s32 getBlockAlignment_() const { return 0x100; }
    virtual u32 getBlockSizeMax_() const { return 0x10000; }
    virtual void verifyStructSize_(u32 size) const {}

    virtual void bindBufferNVN_(NVNcommandBuffer* commandBuffer, NVNshaderStage stage, s32 index,
                                NVNbufferAddress address, size_t size) const {
        nvnCommandBufferBindUniformBuffer(commandBuffer, stage, index, address, size);
    }

private:
    struct Member_ {
        s32 arraySize;
        u16 offset;
        u16 stride;
        u8 type;
    };
    static_assert(sizeof(Member_) == 0xc);

    struct Header_ {
        Member_* members;
        u16 memberNum;
        u16 declaredNum;
    };
    static_assert(sizeof(Header_) == 0x10);

    enum class Flags : u8 {
        HeaderAllocated = 1 << 0,
        BufferAllocated = 1 << 1,
        NvnBufferInitialized = 1 << 2,
    };

    Header_* mHeader = nullptr;

    void* mCurrentBufferData = nullptr;

    u32 mDataSize = 0;
    u32 mBlockSize = 0;
    u32 mBufferSize = 0;

    GPUMemVoidAddr mBuffer;

    u8 mBufferNum = 1;
    u8 mCurrentBufferIndex = 0;
    sead::TypedBitFlag<Flags> mFlags;
    u16 mInstanceNum = 1;

    alignas(8) NVNbuffer mNvnBuffer;
};

static_assert(sizeof(UniformBlock) == 0x78);

}  // namespace agl

#define AGL_COMMON_UNIFORMBLOCK_H_
#include "common/aglUniformBlock.hpp"
#undef AGL_COMMON_UNIFORMBLOCK_H_
