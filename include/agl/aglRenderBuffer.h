#pragma once

#include <basis/seadTypes.h>
#include <gfx/seadColor.h>
#include <gfx/seadFrameBuffer.h>
#include <math/seadBoundBox.h>
#include <math/seadVector.h>

namespace sead {
class DisplayBuffer;
class DrawContext;
}  // namespace sead

namespace agl {

class DrawContext;
class RenderTargetColor;
class RenderTargetDepth;

class RenderBuffer : public sead::FrameBuffer {
public:
    RenderBuffer();
    RenderBuffer(const sead::Vector2f&, const sead::BoundBox2f&);
    RenderBuffer(const sead::Vector2f&, f32, f32, f32, f32);
    ~RenderBuffer() override;

    virtual void copyToDisplayBuffer(sead::DrawContext*, const sead::DisplayBuffer*);
    virtual void clear(sead::DrawContext*, u32, const sead::Color4f&, f32, u32);
    virtual void bindImpl_(sead::DrawContext*) const;

    void initialize_();
    void setRenderTargetColorNullAll();
    void adjustPhysicalAreaAndVirtualSizeFromColorTarget(u32);
    void invalidateGPUCache(DrawContext*) const;
    void bind_(DrawContext*, u16) const;

private:
    u32 _8;
    u32 _c;
    u64 _10;
    u32 _18;
    u32 _1c;
    RenderTargetColor* _20[8];
    RenderTargetDepth* _60;
};

}  // namespace agl
