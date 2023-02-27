#pragma once

#include <container/seadBuffer.h>
#include <heap/seadDisposer.h>
#include <hostio/seadHostIONode.h>
#include "prim/seadSafeString.h"

namespace agl {

class ResBinaryShaderArchive {
private:
    void* mPtr;
};
class ResShaderArchive {
private:
    void* mPtr;
};
class ResShaderProgram;
class ResShaderSource;
class ShaderProgram;
class ShaderProgramEdit;
class ShaderSource;

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
    void setUpFromObjectReflector(bool, bool);
    int searchShaderProgramIndex(const sead::SafeString&) const;
    sead::FormatFixedSafeString<1024> genMessage(sead::hostio::Context* context);
    void listenPropertyEvent(const sead::hostio::PropertyEvent* property_event);

private:
    ResBinaryShaderArchive mBinaryShaderArchive;
    ResShaderArchive mResShaderArchive;
    int mShaderProgramsSize;
    ShaderProgram** mShaderPrograms;
    void* _48[6];
    short _78[2];
    sead::Buffer<ShaderProgramEdit> mShaderProgramEdits;
    int mShaderSourcesSize;
    ShaderSource* mShaderSources;
    int unkArraySize;
    void* unkArray;
    int unkArraySize2;
    bool* unkArray2;
};
static_assert(sizeof(ShaderProgramArchive) == 0xC0);

}  // namespace agl
