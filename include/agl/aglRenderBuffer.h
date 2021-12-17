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
    RenderBuffer(const sead::Vector2<f32>&, const sead::BoundBox2<f32>&);
    RenderBuffer(const sead::Vector2<f32>&, f32, f32, f32, f32);
    ~RenderBuffer() override;

    virtual void copyToDisplayBuffer(sead::DrawContext*, const sead::DisplayBuffer*);
    virtual void clear(sead::DrawContext*, u32, const sead::Color4f&, f32, u32);
    virtual void bindImpl_(sead::DrawContext*) const;

    void initialize_();
    void setRenderTargetColorNullAll();
    void adjustPhysicalAreaAndVirtualSizeFromColorTarget(u32);
    void invalidateGPUCache(agl::DrawContext*) const;
    void bind_(agl::DrawContext*, u16) const;

    u32 _8;
    u32 _c;
    u64 _10;
    u32 _18;
    u32 _1c;
    agl::RenderTargetColor* _20;
    agl::RenderTargetColor* _28;
    agl::RenderTargetColor* _30;
    agl::RenderTargetColor* _38;
    agl::RenderTargetColor* _40;
    agl::RenderTargetColor* _48;
    agl::RenderTargetColor* _50;
    agl::RenderTargetColor* _58;
    agl::RenderTargetDepth* _60;
};
}  // namespace agl
