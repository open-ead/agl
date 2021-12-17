#pragma once

#include <basis/seadTypes.h>
#include <gfx/seadDrawContext.h>
#include <thread/seadCriticalSection.h>

namespace agl {
class RenderBuffer;
class DisplayList;

class DrawContext : public sead::DrawContext {
public:
    DrawContext();
    virtual ~DrawContext();

    void setCommandBuffer(DisplayList*);
    void flushCommandBuffer();
    void setBoundRenderBuffer(u64*);
    void barrierTexture(u32);
    void barrierShader(u32);
    bool isTextureDirty(u32, s32) const;
    void setTextureDirty(s32);
    void setCommandBufferTemporary();

    DisplayList* mDisplayList;
    RenderBuffer* _f8;
    u8 _100;
    u8 _101;
    u8 _102;
    u8 _103;
    u32 _104;
    u32 _10c;
    sead::CriticalSection mCriticalSection;
};
}  // namespace agl
