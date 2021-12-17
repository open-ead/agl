#pragma once

#include <basis/seadTypes.h>

class NVNtextureView;
class NVNtexture;

namespace agl {
namespace driver {
class NVNtexture_ {
public:
    NVNtexture_();
    NVNtexture_(const agl::driver::NVNtexture_&);
    ~NVNtexture_();

    void releaseTexture();
    void updateTexId_(s32 newID);
    // agl::driver:NVNtexture_ operator=(const agl::driver::NVNtexture_&);
    bool registerTexture(const NVNtexture*, const NVNtextureView*, const char*, bool);

    void setReference_() const;

    u8 _0[0xC0];     // NVNtexture
    s32 mTextureID;  // _C0
    u8 _C4;
    u8 _C5;
    u8 _C6;
    u8 _C7;
};
};  // namespace driver
};  // namespace agl
