#pragma once

#include <basis/seadTypes.h>
#include <prim/seadNamable.h>

#include "common/aglShaderEnum.h"

namespace agl {
class ShaderProgram;

class ShaderLocation {
public:
    void setLocation(s32);
    void setLocation(ShaderType, s32);
    void setRegisterLocation(ShaderType, s32);

private:
    union {
        s8 mLocation[cShaderType_Num];
        s16 mRegisterLocation[2];
    };
};

class UniformBlockLocation : public ShaderLocation, public sead::INamable {
    ~UniformBlockLocation();
    void search(const ShaderProgram&);
};

}
