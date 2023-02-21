#pragma once

#include "agl/detail/aglMemoryPoolHeap.h"
#include "aglGPUMemBlock.hpp"

namespace sead {
class Heap;
}

namespace agl {
class GPUMemAddrBase {
public:
    GPUMemAddrBase(const GPUMemBlockBase& memBlock, u64 offset);

    u32 verify_() const;
    void deleteGPUMemBlock() const;
    void invalidate();
    u32 getAlignmentAddress() const;
    void setByteOffsetByPtr(void* ptr);
    void roundUp(int addr);
    void flushCPUCache(u64);
    void invalidateCPUCache(u64);

private:
    detail::MemoryPool* mMemoryPool;
    int mAlignmentAddr;
    GPUMemBlockBase* mMemoryBlock;
};

template <typename T>
class GPUMemAddr : GPUMemAddrBase {};
}  // namespace agl
