#pragma once

#include <nvn/nvn.h>
#include <basis/seadTypes.h>

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
    NVNtexture mTexture;
    s32 mTextureID;
    u8 _c4;
    u8 _c5;
    u8 _c6;
    u8 _c7;
};

}  // namespace agl::driver
