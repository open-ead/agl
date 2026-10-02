#pragma once

#include "common/aglGPUMemBlock.h"
#include "detail/aglMemoryPoolHeap.h"

namespace sead {
class Heap;
}

namespace agl {
class GPUMemAddrBase {
public:
    GPUMemAddrBase() {}
    GPUMemAddrBase(const GPUMemAddrBase& other, int alignmentOffset)
        : mMemoryPool(other.mMemoryPool), mAlignmentAddr(other.mAlignmentAddr + alignmentOffset),
          mMemoryBlock(other.mMemoryBlock) {}
    GPUMemAddrBase(const GPUMemBlockBase& memBlock, u64 offset);

    void deleteGPUMemBlock() const;
    void invalidate();
    u32 getAlignmentAddress() const;
    void setByteOffsetByPtr(void* ptr);
    void roundUp(int addr);
    void flushCPUCache(u64);
    void invalidateCPUCache(u64) const;

    bool isValid() const { return mMemoryPool != nullptr; }

private:
    u32 verify_() const;

    detail::MemoryPool* mMemoryPool = nullptr;
    int mAlignmentAddr = 0;
    GPUMemBlockBase* mMemoryBlock = nullptr;
};

template <typename T>
class GPUMemAddr : public GPUMemAddrBase {
public:
    GPUMemAddr() : GPUMemAddrBase() {}
    GPUMemAddr(const GPUMemBlockBase& memBlock, u64 offset) : GPUMemAddrBase(memBlock, offset) {}
};
}  // namespace agl
