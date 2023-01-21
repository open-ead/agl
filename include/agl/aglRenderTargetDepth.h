#pragma once

#include "agl/aglTextureData.h"

namespace agl {

class RenderTargetDepth : public TextureData {
public:
    RenderTargetDepth();
    RenderTargetDepth(const TextureData&, u32, u32);

    void onApplyTextureData_();
    void initRegs_(u32) const;

private:
    s32 _128;
    u32 _12c;
    u64 _130;
    u64 _138;
    u64 _140;
    u64 _148;
    u8 _150[0x178 - 0x150];
};

}  // namespace agl
