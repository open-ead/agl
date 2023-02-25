#pragma once

#include <basis/seadTypes.h>
#include "common/aglGPUMemAddr.h"

namespace sead {
class Heap;
}

namespace agl {

class DisplayList {
public:
    DisplayList();
    virtual ~DisplayList();

    void setControlMemory(void* memory, s32 size);
    void clear();
    void setBuffer(GPUMemAddr<u8> buffer, u64 size);
    void setValidSize(u64 size);
    void copyTo(DisplayList* other) const;
    void beginDisplayList();
    void endDisplayList();
    bool beginDisplayListBuffer(GPUMemAddr<u8> addr, u64 size, bool invalidate_cpu);
    void endDisplayListBuffer(sead::Heap* heap);
    void adjustValueSize();
    void invalidateCPUCache() const;
    void dump() const;
    bool suspend(void**);     // unused parameter
    void resume(void*, u64);  // unused parameters
    u64 calcRemainingSize();

private:
    GPUMemAddr<u8> mBuffer;
    u32 mUsedSize;
    u32 _24;
    u32 mSize;
    u32 _2c;
    u64 _30;
    void* mControlMemory;
    u8 _40[0x248 - 0x40];    // todo; what is here?
    u32 mControlMemorySize;  // init'd to 0x200
    u32 _24c;
    void* _250;  // only accessed for calls on `pfnc_nvnCommandBuffer...`
    const char* mDisplayName;
};

}  // namespace agl
