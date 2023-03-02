#pragma once

#include "environment/aglEnvObj.h"

namespace agl::env {

// TODO
class AmbientLight : public EnvObj {
public:
    static const TypeInfo* sTypeInfo;
};

// TODO
class DirectionalLight : public EnvObj {
public:
    static const TypeInfo* sTypeInfo;
};

// TODO
class HemisphereLight : public EnvObj {
public:
    static const TypeInfo* sTypeInfo;
};

}  // namespace agl::env
