#pragma once

namespace nn::g3d {
class ResFile;
}  // namespace nn::g3d

namespace agl::g3d {
class ResFile {
public:
    static void Setup(nn::g3d::ResFile*);
    static void BindTexture(nn::g3d::ResFile*, nn::g3d::ResFile*);
    static void Cleanup(nn::g3d::ResFile*);
};
}  // namespace agl::g3d
