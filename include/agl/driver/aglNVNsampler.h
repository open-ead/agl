#pragma once

#include <basis/seadTypes.h>
#include <nvn/nvn.h>

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
    u64 _0;
    s16 _8;
};

}  // namespace agl::driver
