#pragma once

#include <nn/gfx/api.h>
#include <nn/gfx/memory.h>
#include "agl/detail/aglMemoryPool.h"
#include "agl/detail/aglMemoryPoolHeap.h"

namespace sead {
class Heap;
}

namespace agl {
typedef u64 GPUMemVoidAddr;

class GPUMemBlockBase {
public:
    GPUMemBlockBase();

    virtual ~GPUMemBlockBase();

    void clear();
    void freeBuffer();
    void free();
    void allocBuffer_(u64, sead::Heap*, s32, agl::MemoryAttribute);
    bool tryAllocBuffer_(u64, sead::Heap*, s32, agl::MemoryAttribute);
    void setBuffer_(u64, void*, void*, agl::MemoryAttribute);
    void setVirtual_(u64, sead::Heap*, agl::MemoryAttribute, agl::GPUMemVoidAddr, s32);
    void initializeGfxMemoryPool(
        nn::gfx::TMemoryPool<nn::gfx::ApiVariation<nn::gfx::ApiType<4>, nn::gfx::ApiVersion<8>>>*)
        const;
    void addList(agl::GPUMemBlockBase*);
    void setMemoryPool(void*, u64, agl::detail::MemoryPool*);
    void setMemoryPoolHeap(void*, u64, agl::detail::MemoryPoolHeap*);
    u64 getByteOffset() const;
    u64 getMemoryPoolType() const;

    void* mMemBlockBuffer;
    u64 mMemBlockBufferSize;
    agl::detail::MemoryPool* mMemoryPool;
    agl::detail::MemoryPoolHeap* mMemoryPoolHeap;
    u8 _28;  // this is some sort of bitflag
    u8 _29;
    u8 _2a;
    u8 _2b;
    u32 _2c;
    u64 _30;
};

class GPUMemAddrBase {
public:
    GPUMemAddrBase(const agl::GPUMemBlockBase&, u64);

    u32 verify_() const;
    void deleteGPUMemBlock() const;
    void invalidate();
    u32 getAlignmentAddress() const;
    void setByteOffsetByPtr(void*);
    void roundUp(s32);
    void flushCPUCache(u64);
    void invalidateCPUCache(u64);

    agl::detail::MemoryPool* mMemoryPool;
    u32 mAlignmentAddr;
    u32 _c;  // most likely padding bytes
    agl::GPUMemBlockBase* mMemoryBlock;
};

template <typename T>
class GPUMemBlock : public agl::GPUMemBlockBase {
public:
    virtual ~GPUMemBlock();
};

template <typename T>
class GPUMemBlockT : public agl::GPUMemBlockBase {
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
