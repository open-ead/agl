#pragma once

#include <nvn/nvn.h>
#include <basis/seadTypes.h>

namespace agl::driver {

class NVNsampler_ {
public:
    NVNsampler_();
    NVNsampler_(const NVNsampler_& other);
    ~NVNsampler_();

    void releaseSampler();
    bool registerSampler(const NVNsampler& sampler, const char*);
    void updateTextureId(s32);

private:
    void* _0;
    s16 _8;
};

}  // namespace agl::driver
