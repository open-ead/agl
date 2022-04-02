#pragma once

#include <basis/seadTypes.h>

namespace agl::env {

// TODO
class EnvObjSetMgr {
public:
    class InitArg {
    public:
        InitArg();
        virtual ~InitArg() = default;

    private:
        u32 _8 = 0x100;
        u32 _c = 0x40;
    };
};

}  // namespace agl::env
