#pragma once

#include <basis/seadTypes.h>

namespace agl {
namespace driver {
class NVNimage_ {
public:
    NVNimage_();
    NVNimage_(const agl::driver::NVNimage_&);
    ~NVNimage_();

    void updateImageId(s32 id);

    u64 mImageId;  // _0
};
};  // namespace driver
};  // namespace agl
