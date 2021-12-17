#pragma once

#include <basis/seadTypes.h>
#include "agl/gpu.h"

namespace sead {
class Heap;
}

namespace agl {
class DisplayList {
public:
    DisplayList();
    virtual ~DisplayList();

    void setControlMemory(void*, s32);
    void clear();
    void setBuffer(GPUMemAddr<u8>, u64);
    void setValidSize(u64 size);
    void copyTo(DisplayList*) const;
    void beginDisplayList();
    void endDisplayList();
    bool beginDisplayListBuffer(GPUMemAddr<u8>, u64, bool);
    void endDisplayListBuffer(sead::Heap*);
    void adjustValueSize();
    void invalidateCPUCache() const;
    void dump() const;
    bool suspend(void**);
    void resume(void*, u64);
    u64 calcRemainingSize();

private:
    u64 _8;
    u64 _10;
    u64 _18;
    u32 mUsedSize;
    u32 _24;
    u32 mSize;
    u32 _2c;
    u64 _30;
    u64 _38;
    u8 _40[0x248 - 0x40];  // todo; what is here?
    u32 _248;              // init'd to 0x200
    u32 _24c;
    u64 _250;
    char* mDisplayName;
};
}  // namespace agl
