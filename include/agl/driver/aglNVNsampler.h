#pragma once

#include <basis/seadTypes.h>

class NVNsampler;

namespace agl::driver {
class NVNsampler_ {
public:
    NVNsampler_();
    NVNsampler_(const NVNsampler_&);
    ~NVNsampler_();

    void releaseSampler();
    bool registerSampler(const NVNsampler&, const char*);
    void updateTextureId(s32);

private:
    u64 _0;
    s16 _8;
};
}  // namespace agl::driver
