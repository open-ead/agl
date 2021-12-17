#pragma once

#include <basis/seadTypes.h>

class NVNtextureView;
class NVNtexture;

namespace agl::driver {
class NVNtexture_ {
public:
    NVNtexture_();
    NVNtexture_(const NVNtexture_&);
    ~NVNtexture_();

    void releaseTexture();
    void updateTexId_(s32 newID);
    // agl::driver:NVNtexture_ operator=(const NVNtexture_&);
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
