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

    void copyToDisplayBuffer(sead::DrawContext* draw_context, const sead::DisplayBuffer* display_buffer) const override;
    void clear(sead::DrawContext* draw_context, u32 clr_flag, const sead::Color4f& color, f32 depth, u32 stencil) const override;
    void bindImpl_(sead::DrawContext* draw_context) const override;

    void initialize_();
    void setRenderTargetColorNullAll();
    void adjustPhysicalAreaAndVirtualSizeFromColorTarget(u32);
    void invalidateGPUCache(DrawContext*) const;
    void bind_(DrawContext*, u16) const;

private:
    u32 _8;
    u32 _c;
    void* _10;
    u32 _18;
    u32 _1c;
    RenderTargetColor* _20[8];
    RenderTargetDepth* _60;
};

}  // namespace agl
