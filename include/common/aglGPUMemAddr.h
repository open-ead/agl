#pragma once

#include <nvn/nvn_FuncPtrInline.h>

#include "common/aglGPUMemBlock.h"
#include "detail/aglGPUMemBlockMgr.h"
#include "detail/aglMemoryPoolHeap.h"

namespace sead {
class Heap;
}

namespace agl {
class GPUMemAddrBase {
public:
    GPUMemAddrBase() {}
    GPUMemAddrBase(const GPUMemAddrBase& other) : GPUMemAddrBase(other, 0) {}
    GPUMemAddrBase(const GPUMemAddrBase& other, s32 alignmentOffset)
        : mMemoryPool(other.mMemoryPool), mAlignmentAddr(other.mAlignmentAddr + alignmentOffset),
          mMemoryBlock(other.mMemoryBlock) {}

    GPUMemAddrBase(const GPUMemBlockBase& memBlock, size_t offset);

    GPUMemAddrBase& operator=(const GPUMemAddrBase& other) = default;

    void destroy() {
        if (isValid()) {
            deleteGPUMemBlock();
            invalidate();
        }
    }

    void deleteGPUMemBlock() const;
    void invalidate();

    u32 getAlignmentAddress() const;
    void setByteOffsetByPtr(void* ptr);
    void roundUp(int addr);
    void flushCPUCache(size_t);
    void invalidateCPUCache(size_t) const;

    bool isValid() const { return mMemoryPool != nullptr; }

    detail::MemoryPool* getMemoryPool() const { return mMemoryPool; }
    u32 getByteOffset() const { return mAlignmentAddr; }
    GPUMemBlockBase* getMemoryBlock() const { return mMemoryBlock; }

private:
    u32 verify_() const;

    detail::MemoryPool* mMemoryPool = nullptr;
    s32 mAlignmentAddr = 0;
    GPUMemBlockBase* mMemoryBlock = nullptr;
};

template <typename T>
class GPUMemAddr : public GPUMemAddrBase {
public:
    GPUMemAddr() {}
    GPUMemAddr(const GPUMemAddrBase& other) : GPUMemAddrBase(other, 0) {}
    GPUMemAddr(const GPUMemBlock<T>& memBlock) : GPUMemAddrBase(memBlock, 0) {}
    GPUMemAddr(const GPUMemBlock<T>& memBlock, size_t offset) : GPUMemAddrBase(memBlock, offset) {}

    static GPUMemAddr alloc(size_t size, sead::Heap* heap, s32 alignment,
                            MemoryAttribute attribute = MemoryAttribute::Default) {
        auto* block = new (heap) GPUMemBlock<T>;
        block->allocBuffer(size, heap, alignment, attribute);

        return GPUMemAddr(*block);
    }

    T* getData() const {
        u32 offset = getByteOffset();
        return static_cast<T*>(
            sead::PtrUtil::addOffset(isValid() ? getMemoryPool()->map() : nullptr, offset));
    }
};

class GPUMemVoidAddr : public GPUMemAddrBase {
public:
    GPUMemVoidAddr() {}
    GPUMemVoidAddr(const GPUMemAddrBase& other) : GPUMemAddrBase(other) {}
    GPUMemVoidAddr(const GPUMemAddrBase& other, s32 alignmentOffset)
        : GPUMemAddrBase(other, alignmentOffset) {}
    GPUMemVoidAddr(const GPUMemBlockBase& memBlock) : GPUMemAddrBase(memBlock, 0) {}
    GPUMemVoidAddr(const GPUMemBlockBase& memBlock, size_t offset)
        : GPUMemAddrBase(memBlock, offset) {}

    static GPUMemVoidAddr alloc(size_t size, sead::Heap* heap, s32 alignment,
                                MemoryAttribute attribute = MemoryAttribute::Default) {
        auto* block = new (heap) GPUMemBlock<u8>;
        block->allocBuffer(size, heap, alignment, attribute);

        return GPUMemVoidAddr(*block);
    }

    void* getData() const {
        u32 offset = getByteOffset();
        return sead::PtrUtil::addOffset(isValid() ? getMemoryPool()->map() : nullptr, offset);
    }
};

class ConstGPUMemVoidAddr : public GPUMemAddrBase {
public:
    ConstGPUMemVoidAddr(const GPUMemAddrBase& other, s32 alignmentOffset)
        : GPUMemAddrBase(other, alignmentOffset) {}
    ConstGPUMemVoidAddr(const GPUMemBlockBase& memBlock) : GPUMemAddrBase(memBlock, 0) {}
    ConstGPUMemVoidAddr(const GPUMemBlockBase& memBlock, size_t offset)
        : GPUMemAddrBase(memBlock, offset) {}

    const void* getData() const {
        u32 offset = getByteOffset();
        return sead::PtrUtil::addOffset(isValid() ? getMemoryPool()->map() : nullptr, offset);
    }
};

}  // namespace agl
