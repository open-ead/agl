#pragma once

#include <agl/util.h>
#include <basis/seadTypes.h>
#include <nvn/nvn_types.h>

namespace agl::detail {
struct SurfaceBase;

class Surface {
public:
    Surface();
    void initialize(TextureType, TextureFormat, u32, TextureAttribute,
                    MultiSampleType);
    void initializeSize(u32, u32, u32);
    void copyFrom(const SurfaceBase&);
    void calcSizeAndAlignment();
    void setupNVNtextureBuilder(NVNtextureBuilder*) const;
    void printInfo() const;
    void copyFrom(const NVNtexture&);

private:
    u16 _0;
    u16 _2;
    u16 _4;
    u16 _6;
    u8 _8;
    u8 _9;
    u16 _a;
    u8 _c[0x1A - 0xC];
    u8 _1a;
    u8 _1b;
    u32 _1c;
    u8 _20;
    u8 _21;
    u8 _22;
    u8 _23;
};

struct SurfaceBase {
    u64 _0;
    u64 _8;
    u64 _10;
};
}  // namespace agl::detail
