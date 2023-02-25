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
    RenderBuffer(const sead::Vector2f& virtual_size, const sead::BoundBox2f& physical_area);
    RenderBuffer(const sead::Vector2f& virtual_size, f32 physical_x, f32 physical_y, f32 physical_w,
                 f32 physical_h);
    ~RenderBuffer() override;

    void copyToDisplayBuffer(sead::DrawContext* draw_context,
                             const sead::DisplayBuffer* display_buffer) const override;
    void clear(sead::DrawContext* draw_context, u32 clr_flag, const sead::Color4f& color, f32 depth,
               u32 stencil) const override;
    void bindImpl_(sead::DrawContext* draw_context) const override;

    void initialize_();
    void setRenderTargetColorNullAll();
    void adjustPhysicalAreaAndVirtualSizeFromColorTarget(u32 color_index);
    void invalidateGPUCache(DrawContext* draw_context) const;
    void bind_(DrawContext* draw_context, u16 bitmap) const;

private:
    RenderTargetColor* mRenderTargetColor[8];
    RenderTargetDepth* mRenderTargetDepth;
};

}  // namespace agl
