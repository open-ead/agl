#pragma once

#include <nn/gfx/api.h>
#include <nn/gfx/memory.h>
#include "agl/detail/aglMemoryPoolHeap.h"
#include "aglGPUMemBlock.hpp"

namespace sead {
class Heap;
}

namespace agl {
class GPUMemAddrBase {
public:
    GPUMemAddrBase(const GPUMemBlockBase&, u64);

    u32 verify_() const;
    void deleteGPUMemBlock() const;
    void invalidate();
    u32 getAlignmentAddress() const;
    void setByteOffsetByPtr(void*);
    void roundUp(s32);
    void flushCPUCache(u64);
    void invalidateCPUCache(u64);

private:
    detail::MemoryPool* mMemoryPool;
    u32 mAlignmentAddr;
    u32 _c;  // most likely padding bytes
    GPUMemBlockBase* mMemoryBlock;
};

template <typename T>
class GPUMemBlock : public GPUMemBlockBase {
public:
    virtual ~GPUMemBlock();
};

template <typename T>
class GPUMemBlockT : public GPUMemBlockBase {
public:
    virtual ~GPUMemBlockT();
};

template <typename T>
class GPUMemAddr {
public:
    u64* mPtr;
    u64 _8;
};
}  // namespace agl
