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
    virtual ~DrawContext();

    void setCommandBuffer(DisplayList*);
    void flushCommandBuffer();
    void setBoundRenderBuffer(u64*);
    void barrierTexture(u32);
    void barrierShader(u32);
    bool isTextureDirty(u32, s32) const;
    void setTextureDirty(s32);
    void changeShaderType(ShaderMode mode, ShaderOptimizeType optimizeType);
    void setCommandBufferTemporary();

private:
    void* gap[5];
    agl::DisplayList* mDisplayList;
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
