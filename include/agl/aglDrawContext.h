#pragma once

#include <basis/seadTypes.h>
#include <gfx/seadDrawContext.h>
#include <thread/seadCriticalSection.h>
#include "prim/seadRuntimeTypeInfo.h"

namespace agl {

class RenderBuffer;
class DisplayList;
enum ShaderMode {};
enum ShaderOptimizeType {};

class DrawContext : public sead::DrawContext {
    SEAD_RTTI_OVERRIDE(DrawContext, sead::DrawContext)
public:
    DrawContext();
    ~DrawContext() override;

    void setCommandBuffer(DisplayList* buffer);
    void flushCommandBuffer();
    void setBoundRenderBuffer(const RenderBuffer* buffer);
    void barrierTexture(u32 flags);
    void barrierShader(u32 flags);
    bool isTextureDirty(u32 unused, s32 index) const;
    void setTextureDirty(s32 index);
    void changeShaderType(ShaderMode mode, ShaderOptimizeType optimizeType);
    void setCommandBufferTemporary();

private:
    void* gap[5];
    agl::DisplayList* mCommandBuffer;
    const agl::RenderBuffer* mBoundRenderBuffer;
    u8 _100;
    ShaderMode mShaderMode;
    u8 _102;
    u8 _103;
    u32 _104;
    u32 _10c;
    void* gap2[19];
    long mTextureDirty;
};

}  // namespace agl
