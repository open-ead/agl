#pragma once

#include <basis/seadTypes.h>

namespace agl::driver {
class NVNimage_ {
public:
    NVNimage_();
    NVNimage_(const NVNimage_&);
    ~NVNimage_();

    void updateImageId(s32 id);

    u64 mImageId;
};
}  // namespace agl::driver
