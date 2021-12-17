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
    u64 _138;
    u64 _140;
    u64 _148;
    u64 _150;
    u64 _158;
    u64 _160;
    u64 _168;
    u64 _170;
};
}  // namespace agl
