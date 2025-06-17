#pragma once

#include <basis/seadTypes.h>

namespace nn::g3d {
class ResFile;
}

namespace agl::g3d {

class ResFile {
public:
    static void Setup(nn::g3d::ResFile*);
    static void Cleanup(nn::g3d::ResFile*);
    static s32 GetTextureIndex(const nn::g3d::ResFile*, const char*);
    static bool BindTexture(nn::g3d::ResFile*, const nn::g3d::ResFile*);
};

}  // namespace agl::g3d
