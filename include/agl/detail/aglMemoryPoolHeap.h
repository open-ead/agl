#pragma once

#include <basis/seadTypes.h>

namespace agl {

class GPUMemBlockBase;

namespace detail {

class GPUMemBlockMgrHeapEx;
class MemoryPoolType;

class MemoryPoolHeap {
public:
    MemoryPoolHeap(void*, u64, u64, const MemoryPoolType&, void*, u64, GPUMemBlockMgrHeapEx*);
    ~MemoryPoolHeap();

    static MemoryPoolHeap* create(u64, s32, u64, s32, u64, u64, const MemoryPoolType&,
                                  GPUMemBlockMgrHeapEx*);
    static void destroy(MemoryPoolHeap*);

    void pushBack(GPUMemBlockBase*);
    u64* allocFromMemoryPool(u64, s32);
    void freeToHeap(GPUMemBlockBase*);
    bool isAllocatable(const MemoryPoolType&, u64, s32) const;

private:
    GPUMemBlockBase* _120;
};

}  // namespace detail
}  // namespace agl
