#pragma once

#include <prim/seadSafeString.h>
#include "common/aglDisplayList.h"
#include "common/aglShader.h"

namespace sead {
class Heap;
}

namespace agl {

class ShaderProgram {
public:
    class VariationBuffer {
    public:
        void initialize(s32, sead::Heap*);
        void createMacro(s32, const sead::SafeString&, const sead::SafeString&, s32, sead::Heap*);
        void setMacroValue(s32, s32, const sead::SafeString&);
        void create(sead::Heap*);
    };

    ShaderProgram();

    virtual ~ShaderProgram();

    void cleanUp();
    void destroyLocationBuffers();
    void initializeVariation(const sead::SafeString&, s32, sead::Heap*);
    void createVariationMacro(s32, const sead::SafeString&, const sead::SafeString&, s32,
                              sead::Heap*);
    void setVariationMacroValue(s32, s32, const sead::SafeString&);
    void createVariation(sead::Heap*);

private:
    u64* _8;
    DisplayList mShaderDisplayList;  // _10
    u32 _278;
    u32 _27c;
    void* _280;
    u32 _288;
    u32 _28c;
    void* _290;
    u32 _298;
    u32 _29c;
    void* _2a0;
    u32 _2a8;
    u32 _2ac;
    void* _2b0;
    u32 _2b8;
    u32 _2bc;
    void* _2c0;
    u32 _2c8;
    u32 _2cc;
    void* _2d0;
    VertexShader mVertexShader;
    FragmentShader mFragmentShader;
    GeometryShader mGeometryShader;
    ComputeShader mComputeShader;
    u8 _358[0x418 - 0x358];  // todo; what is here?
    void* _418;
    u32 _420;
};

}  // namespace agl
