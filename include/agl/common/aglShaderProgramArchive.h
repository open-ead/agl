#pragma once

#include <heap/seadDisposer.h>
#include <hostio/seadHostIONode.h>

namespace agl {

class ResBinaryShaderArchive;
class ResShaderArchive;
class ResShaderProgram;
class ResShaderSource;

class ShaderProgramArchive : public sead::IDisposer, public sead::hostio::Node {
public:
    ShaderProgramArchive();
    virtual ~ShaderProgramArchive();

    void destroy();
    void createWithOption(ResBinaryShaderArchive, ResShaderArchive, u32, sead::Heap*);
    void destroyResFile_();
    void initialize(ShaderProgramArchive*, s32, ResShaderProgram, sead::Heap*);
    void updateCompileInfo();
    void setUp();
    void setUp_(bool);

private:
    void* _20;
    ResBinaryShaderArchive* mBinaryShaderArchive;
    ResShaderArchive* mResShaderArchive;
};

}  // namespace agl
