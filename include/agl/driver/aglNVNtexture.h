#pragma once

#include <basis/seadTypes.h>
#include <nvn/nvn_types.h>

namespace agl::driver {
class NVNtexture_ {
public:
    NVNtexture_();
    NVNtexture_(const NVNtexture_& other);
    ~NVNtexture_();

    void releaseTexture();
    void updateTexId_(s32 newID);
    NVNtexture_ operator=(const NVNtexture_& other);
    bool registerTexture(const NVNtexture*, const NVNtextureView*, const char*, bool);

    void setReference_() const;

private:
    u8 _0[0xC0];  // NVNtexture
    s32 mTextureID;
    u8 _c4;
    u8 _c5;
    u8 _c6;
    u8 _c7;
};
}  // namespace agl::driver
