#pragma once

#include <container/seadPtrArray.h>
#include <hostio/seadHostIONode.h>
#include "agl/shader/aglShader.h"

namespace sead {
class Heap;
}

namespace agl {
class ShaderCompileInfo : public sead::hostio::Node {
    // this value is used as an index to a table of version lists
    // on SMO 1.2.0, located at 0x7101E80B30
    typedef s32 Target;

    ShaderCompileInfo();

    virtual ~ShaderCompileInfo();

    void destroy();
    void create(s32, s32 bufferSize, sead::Heap*);
    void clearVariation();
    void pushBackVariation(char const*, char const*);
    void calcCompileSource(ShaderType, sead::BufferedSafeString*,
                           ShaderCompileInfo::Target, bool);
    sead::SafeString* getRegitserUniformBlockName();  // "RegisterUBO"

    u64 _8;
    char* mName;  // _10
    u64 _18;
    u64 _20;
    sead::PtrArrayImpl _28;
    sead::PtrArrayImpl _38;
    sead::PtrArrayImpl _48;
    sead::PtrArrayImpl _58;
};
}  // namespace agl
