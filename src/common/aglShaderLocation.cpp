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

UniformBlockLocation::~UniformBlockLocation() = default;

static s32 getLocation(const UniformBlockLocation& loc, const ShaderProgram& program,
                       ShaderType type) {
    if (!program.hasStage(type))
        return -1;

    const Shader& shader = program.getShader(type);
    const void* data = shader.getShaderBinary();
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

    UniformBlock* uniformBlocks = shaderBinary->uniformBlocks;

    // TODO: probably an inlined search function returning UniformBlock*
    for (u32 i = 0; i < numUniformBlocks; i++) {
        if (strcmp(uniformBlocks[i].name, name) == 0) {
            if (&uniformBlocks[i])
                return uniformBlocks[i].location;
            return -1;
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
