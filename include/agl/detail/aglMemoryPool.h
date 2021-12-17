#pragma once

#include <basis/seadTypes.h>

namespace agl {
typedef s32 MemoryAttribute;

namespace detail {
class MemoryPoolType {
public:
    static s32 convert(MemoryAttribute);

    static u32 cInvalidPoolType;  // 0
    static u32 cValidPoolType;    // 0x80000000
};

class MemoryPool {
public:
    MemoryPool();

    void initialize(void*, u64, const MemoryPoolType&);
    void initialize(void*, u64, const MemoryPoolType&, const MemoryPool&, s32);

    void finalize();

private:
    u8 _0[0x104];  // todo: where do the parent 0x100 bytes come from?
};
}  // namespace detail
}  // namespace agl