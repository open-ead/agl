#pragma once

#include <heap/seadDisposer.h>

namespace agl {
namespace detail {
class ShaderHolder {
    SEAD_SINGLETON_DISPOSER(ShaderHolder)
public:
    ShaderHolder();
};
}  // namespace detail
}  // namespace agl
