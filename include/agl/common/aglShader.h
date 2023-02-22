#pragma once

#include <basis/seadTypes.h>

namespace agl {

enum ShaderType {
    ShaderType_Vertex = 0,
    ShaderType_Fragment = 1,
    ShaderType_Geometry = 2,
    ShaderType_Compute = 3
};

class Shader {
public:
    Shader();

    virtual ~Shader();

    virtual s32 getShaderType() const = 0;
    virtual s32 getShaderMode() const;
    virtual s32 getRingItemSize() const;

    void setBinary(const void* shaderBinary);

private:
    void* mShaderBinary;  // _8
    void* _10;
    void* _18;
};

class VertexShader : public Shader {
public:
    virtual ~VertexShader();

    s32 getShaderType() const override;
};

class FragmentShader : public Shader {
public:
    virtual ~FragmentShader();

    s32 getShaderType() const override;
};

class GeometryShader : public Shader {
public:
    virtual ~GeometryShader();

    s32 getShaderType() const override;
};

class ComputeShader : public Shader {
public:
    virtual ~ComputeShader();

    s32 getShaderType() const override;
};

}  // namespace agl
