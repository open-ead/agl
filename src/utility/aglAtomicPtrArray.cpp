#include "utility/aglAtomicPtrArray.h"
#include <algorithm>
#include <basis/seadNew.h>

namespace agl::detail {

void AtomicPtrArrayImpl::setBuffer(s32 ptrNumMax, void* buf) {
    if (ptrNumMax >= 1) {
        if (!buf) {
            SEAD_ASSERT_MSG(false, "buf is null");
            return;
        }

        mPtrs = static_cast<void**>(buf);
        mPtrNum = 0;
        mPtrNumMax = ptrNumMax;
    } else {
        SEAD_ASSERT_MSG(false, "ptrNumMax[%d] must be larger than zero", ptrNumMax);
    }
}

void AtomicPtrArrayImpl::allocBuffer(s32 ptrNumMax, sead::Heap* heap, s32 alignment) {
    SEAD_ASSERT(mPtrs == nullptr);

    if (ptrNumMax >= 1)
        setBuffer(ptrNumMax, new (heap, alignment) u8[s32(sizeof(void*)) * ptrNumMax]);
    else
        SEAD_ASSERT_MSG(false, "ptrNumMax[%d] must be larger than zero", ptrNumMax);
}

void AtomicPtrArrayImpl::freeBuffer() {
    if (isBufferReady()) {
        delete[] mPtrs;
        mPtrs = nullptr;
        mPtrNum = 0;
        mPtrNumMax = 0;
    }
}

void AtomicPtrArrayImpl::erase(s32 pos, s32 count) {
    if (pos < 0) {
        SEAD_ASSERT_MSG(false, "illegal position[%d]", pos);
        return;
    }

    if (count < 0) {
        SEAD_ASSERT_MSG(false, "illegal number[%d]", count);
        return;
    }

    const s32 end_pos = pos + count;
    const s32 ptr_num = mPtrNum;

    if (pos + count > ptr_num) {
        SEAD_ASSERT_MSG(false, "pos[%d] + num[%d] exceed size[%d]", pos, count, ptr_num);
        return;
    }

    if (ptr_num > end_pos)
        sead::MemUtil::copyOverlap(mPtrs + pos, mPtrs + end_pos,
                                   sizeof(void*) * (ptr_num - end_pos));

    mPtrNum = ptr_num - count;
}

void AtomicPtrArrayImpl::shuffle(sead::Random* random) {
    SEAD_ASSERT(random);
    for (s32 i = mPtrNum - 1; i > 0; --i)
        swap(i, random->getS32Range(0, i + 1));
}

void AtomicPtrArrayImpl::sort(CompareCallbackImpl cmp) {
    void** ptrs = mPtrs;
    if (mPtrNum < 2)
        return;

    s32 begin = 0;
    s32 end = mPtrNum - 1;
    do {
        s32 last = begin;
        for (s32 i = begin; i < end; ++i) {
            if (cmp(ptrs[i], ptrs[i + 1]) > 0) {
                void* tmp = ptrs[i + 1];
                ptrs[i + 1] = ptrs[i];
                ptrs[i] = tmp;
                last = i;
            }
        }

        end = last;
        if (begin == end)
            break;

        last = end;
        for (s32 i = end; i > begin; --i) {
            if (cmp(ptrs[i], ptrs[i - 1]) < 0) {
                void* tmp = ptrs[i - 1];
                ptrs[i - 1] = ptrs[i];
                ptrs[i] = tmp;
                last = i;
            }
        }
        begin = last;
    } while (begin != end);
}

void AtomicPtrArrayImpl::heapSort(CompareCallbackImpl cmp) {
    s32 size = mPtrNum;
    if (size < 2)
        return;

    void** ptrs = mPtrs;
    s32 parent = size / 2;
    do {
        void* value = ptrs[parent - 1];
        s32 hole = parent;
        s32 child = parent * 2;

        while (child <= size) {
            s32 selected = child;
            if (child < size && cmp(ptrs[child - 1], ptrs[child]) < 0)
                ++selected;

            if (cmp(value, ptrs[selected - 1]) >= 0)
                break;

            ptrs[hole - 1] = ptrs[selected - 1];
            hole = selected;
            child = selected * 2;
        }

        ptrs[hole - 1] = value;
    } while (parent-- > 1);

    while (size >= 2) {
        const s32 last = size - 1;
        void* value = ptrs[last];
        ptrs[last] = ptrs[0];

        s32 hole = 1;
        s32 child = 2;
        while (child < size) {
            s32 selected = child;
            if (child < last && cmp(ptrs[child - 1], ptrs[child]) < 0)
                ++selected;

            if (cmp(value, ptrs[selected - 1]) >= 0)
                break;

            ptrs[hole - 1] = ptrs[selected - 1];
            hole = selected;
            child = selected * 2;
        }

        ptrs[hole - 1] = value;
        size = last;
    }
}

}  // namespace agl::detail
