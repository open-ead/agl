#include "common/aglShaderLocation.h"

#include <cstring>

#include "common/aglShaderProgram.h"

namespace agl {

void ShaderLocation::setLocation(s32 location) {
    for (s32 i = 0; i < cShaderType_Num; ++i) {
        mLocation[i] = location;
    }
}

void ShaderLocation::setLocation(ShaderType type, s32 location) {
    mLocation[type] = location;
}

void ShaderLocation::setRegisterLocation(ShaderType type, s32 location) {
    mRegisterLocation[type != cShaderType_Vertex] = location;
}

static s32 getLocation(const UniformBlockLocation& loc, const ShaderProgram& program,
                       ShaderType type) {
    if (!program.hasStage(type))
        return -1;

    const void* data = program.getShader(type).getShaderBinary();
    if (!data)
        return -1;

    // TODO: replace with proper types in headers
    using UniformBlock = struct {
        const char* name;
        u32 location;
    };
    using ShaderBinary = struct {
        u8 _0[0x14];
        u32 numUniformBlocks;
        UniformBlock* uniformBlocks;
    };

    const ShaderBinary* shaderBinary = reinterpret_cast<const ShaderBinary*>(data);
    const char* name = loc.getName().cstr();
    u32 numUniformBlocks = shaderBinary->numUniformBlocks;
    if (numUniformBlocks == 0)
        return -1;

    // TODO: probably an inlined search function returning UniformBlock*
    for (u32 i = 0; i < numUniformBlocks; i++) {
        if (strcmp(shaderBinary->uniformBlocks[i].name, name) == 0) {
            if (&shaderBinary->uniformBlocks[i])
                return shaderBinary->uniformBlocks[i].location;
            break;
        }
    }

    return -1;
}

void UniformBlockLocation::search(const ShaderProgram& program) {
    for (s32 i = 0; i < cShaderType_Num; ++i) {
        ShaderType type = static_cast<ShaderType>(i);
        setLocation(type, getLocation(*this, program, type));
    }
}

}  // namespace agl
