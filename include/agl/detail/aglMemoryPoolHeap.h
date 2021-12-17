#pragma once

#include <basis/seadTypes.h>

namespace agl {
class GPUMemBlockBase;

namespace detail {
class GPUMemBlockMgrHeapEx;
class MemoryPoolType;

class MemoryPoolHeap {
public:
    MemoryPoolHeap(void*, u64, u64, const agl::detail::MemoryPoolType&, void*, u64,
                   agl::detail::GPUMemBlockMgrHeapEx*);
    ~MemoryPoolHeap();

    static agl::detail::MemoryPoolHeap* create(u64, s32, u64, s32, u64, u64,
                                               const agl::detail::MemoryPoolType&,
                                               agl::detail::GPUMemBlockMgrHeapEx*);
    static void destroy(agl::detail::MemoryPoolHeap*);

    void pushBack(agl::GPUMemBlockBase*);
    u64* allocFromMemoryPool(u64, s32);
    void freeToHeap(agl::GPUMemBlockBase*);
    bool isAllocatable(const agl::detail::MemoryPoolType&, u64, s32) const;

    agl::GPUMemBlockBase* _120;
};
}  // namespace detail
}  // namespace agl
