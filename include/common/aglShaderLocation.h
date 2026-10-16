#pragma once

#include <basis/seadTypes.h>
#include <prim/seadNamable.h>

#include "common/aglShaderEnum.h"

namespace agl {
class DrawContext;
class ShaderProgram;

class ShaderLocation {
public:
    void setLocation(s32);
    void setLocation(ShaderType, s32);
    void setRegisterLocation(ShaderType, s32);

    bool isValid() const { return mUniformLocation != -1; }

    s8 getLocation(ShaderType type) const { return mLocation[type]; }

private:
    union {
        s8 mLocation[cShaderType_Num];
        s16 mRegisterLocation[2];
        s32 mUniformLocation;
    };
};

class UniformLocation : public ShaderLocation, public sead::INamable {
public:
    UniformLocation(const sead::SafeString& name) : INamable(name) {}
    UniformLocation(const sead::SafeString& name, const ShaderProgram& shader) : INamable(name) {
        search(shader);
    }

    ~UniformLocation() = default;

    void search(const ShaderProgram& shader);
    void setUniformNVN(DrawContext* context, u32 dwSize, const void* data);
};

class SamplerLocation : public ShaderLocation, public sead::INamable {
public:
    SamplerLocation(const sead::SafeString& name) : INamable(name) {}
    SamplerLocation(const sead::SafeString& name, const ShaderProgram& shader) : INamable(name) {
        search(shader);
    }

    ~SamplerLocation() = default;

    void search(const ShaderProgram& shader);
};

class ImageLocation : public ShaderLocation, public sead::INamable {
public:
    ImageLocation(const sead::SafeString& name) : INamable(name) {}
    ImageLocation(const sead::SafeString& name, const ShaderProgram& shader) : INamable(name) {
        search(shader);
    }

    ~ImageLocation() = default;

    void search(const ShaderProgram& shader);
};

class UniformBlockLocation : public ShaderLocation, public sead::INamable {
public:
    UniformBlockLocation(const sead::SafeString& name) : INamable(name) {}
    UniformBlockLocation(const sead::SafeString& name, const ShaderProgram& shader)
        : INamable(name) {
        search(shader);
    }

    ~UniformBlockLocation() = default;

    void search(const ShaderProgram& shader);
};

class ShaderStorageBlockLocation : public ShaderLocation, public sead::INamable {
public:
    ShaderStorageBlockLocation(const sead::SafeString& name) : INamable(name) {}
    ShaderStorageBlockLocation(const sead::SafeString& name, const ShaderProgram& shader)
        : INamable(name) {
        search(shader);
    }

    ~ShaderStorageBlockLocation() = default;

    void search(const ShaderProgram& shader);
};

class AttributeLocation : public ShaderLocation, public sead::INamable {
public:
    AttributeLocation(const sead::SafeString& name, s32 param_2);
    AttributeLocation(const sead::SafeString& name, s32 param_2, const ShaderProgram& shader)
        : AttributeLocation(name, param_2) {
        search(shader);
    }

    ~AttributeLocation() = default;

    void search(const ShaderProgram& shader);
};

}  // namespace agl
