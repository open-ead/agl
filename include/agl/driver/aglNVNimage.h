#pragma once

#include <basis/seadTypes.h>

namespace agl::driver {

class NVNimage_ {
public:
    NVNimage_();
    NVNimage_(const NVNimage_& other);
    ~NVNimage_();

    NVNimage_ operator=(const NVNimage_& other);
    void updateImageId(s32 id);

private:
    u64 mImageId;
};

}  // namespace agl::driver
