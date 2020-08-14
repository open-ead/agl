#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>

namespace agl::utl {

// TODO
class ParameterBase {
public:
    static u32 calcHash(const sead::SafeString& key);
};

}  // namespace agl::utl
