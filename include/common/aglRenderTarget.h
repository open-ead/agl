#pragma once

#include "common/aglTextureData.h"

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

class RenderTargetDepth : public TextureData {
public:
    RenderTargetDepth();
    RenderTargetDepth(const TextureData&, u32, u32);

    void onApplyTextureData_();
    void initRegs_(u32) const;

private:
    s32 _128;
    u32 _12c;
    void* _130;
    void* _138;
    void* _140;
    void* _148;
    u8 _150[0x178 - 0x150];
};

}  // namespace agl
