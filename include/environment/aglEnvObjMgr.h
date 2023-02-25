#pragma once

#include "environment/aglEnvObjBuffer.h"

namespace agl::env {

// TODO
class EnvObjMgr {
public:
    class InitArg : public EnvObjBuffer::AllocateArg {
    public:
        InitArg();

    private:
        u32 _20c = 0x100;
        u32 _210 = 1;
    };
};

}  // namespace agl::env
