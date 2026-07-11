#include "detail/aglGPUMemBlockMgr.h"

namespace agl::detail {
const MemoryPoolType MemoryPoolType::cInvalidPoolType(0);
const MemoryPoolType MemoryPoolType::cValidPoolType(VALID_POOL_TYPE_VALUE);

SEAD_SINGLETON_DISPOSER_IMPL(GPUMemBlockMgr)

GPUMemBlockMgr::GPUMemBlockMgr() {
    mMinBlockSize = cGPUPhysicalMemorySizeAlignment;
    mFlags = GPUMemBlockMgrFlags::EnablePoolSharing;
}

GPUMemBlockMgr::~GPUMemBlockMgr() {
    mMngrHeaps.freeBuffer();
}

void GPUMemBlockMgr::initialize(sead::Heap* heap1, sead::Heap* heap2) {
    mMngrHeaps.allocBuffer(0x1000, heap1);
    mMngrHeaps.clear();
}

void GPUMemBlockMgr::enableSharedMemoryPool(bool enabled) {
    mFlags.change(GPUMemBlockMgrFlags::EnablePoolSharing, enabled);
}

u64 GPUMemBlockMgr::calcGPUMemorySize(u64 userSize) {
    return sead::MathSizeT::roundUp(userSize, cGPUPhysicalMemorySizeAlignment);
}

s32 GPUMemBlockMgr::calcGPUMemoryAlignment(s32 userAlignment) {
    return sead::Mathi::roundUpPow2(sead::Mathi::abs(userAlignment),
                                    cGPUPhysicalMemorySizeAlignment) *
           sead::Mathi::sign(userAlignment);
}

GPUMemBlockMgrHeapEx* GPUMemBlockMgr::findGPUMemBlockMgrHeapEx_(sead::Heap* p_heap,
                                                                int* p_outIndex) {
    SEAD_ASSERT(p_heap != nullptr);

    const int size = mMngrHeaps.size();
    if (size == 0)
        return nullptr;

    int index;
    GPUMemBlockMgrHeapEx* result;
    int right = size - 1;
    if (right < 0) {
        result = nullptr;
    } else {
        auto** managers = mMngrHeaps.data();
        int left = 0;
        while (true) {
            index = right - ~left - 1;
            index /= 2;
            auto* manager = managers[index];
            const intptr_t difference =
                reinterpret_cast<intptr_t>(manager->getDisposerHeap()) -
                reinterpret_cast<intptr_t>(p_heap);
            if (difference == 0) {
                result = u32(size) > u32(index) ? manager : nullptr;
                break;
            }
            left = difference >= 0 ? left : index + 1;
            right = difference < 0 ? right : index - 1;
            if (left > right) {
                result = nullptr;
                break;
            }
        }
    }

    if (p_outIndex)
        *p_outIndex = index;
    return result;
}

GPUMemBlockMgrHeapEx::GPUMemBlockMgrHeapEx(sead::Heap* p_heap)
    : sead::IDisposer(p_heap, sead::IDisposer::HeapNullOption::AlwaysUseSpecifiedHeap),
      mAllowSharing(1), m08(nullptr), m10(nullptr) {
}

}  // namespace agl::detail
