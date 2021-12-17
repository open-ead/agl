#pragma once

#include <heap/seadDisposer.h>

namespace agl::detail {
class ShaderHolder {
    SEAD_SINGLETON_DISPOSER(ShaderHolder)
public:
    ShaderHolder();
};
}  // namespace agl::detail
