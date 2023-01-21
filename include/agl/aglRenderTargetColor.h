#pragma once

#include "agl/aglTextureData.h"

namespace agl {

class RenderTargetColor : public TextureData {
public:
    RenderTargetColor();
    RenderTargetColor(const TextureData&, u32, u32);

    void onApplyTextureData_();
    void initRegs_(u32) const;

private:
    s32 _128;
    u32 _12c;
    u32 _130;
    u32 _134;
    void* _138;
    void* _140;
    void* _148;
    void* _150;
    void* _158;
    void* _160;
    void* _168;
    void* _170;
};

}  // namespace agl
