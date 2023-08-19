#pragma once

#include <container/seadPtrArray.h>
#include <hostio/seadHostIONode.h>
#include "common/aglShader.h"
#include "common/aglShaderEnum.h"

namespace sead {
class Heap;
}

// more information:
// https://github.com/aboood40091/sead/blob/master/packages/agl/include/common/aglShaderCompileInfo.h
namespace agl {

class ShaderCompileInfo : public sead::hostio::Node {
    // this value is used as an index to a table of version lists
    // on SMO 1.2.0, located at 0x7101E80B30
    using Target = s32;

    ShaderCompileInfo();

    virtual ~ShaderCompileInfo();

    void destroy();
    void create(s32, s32 bufferSize, sead::Heap*);
    void clearVariation();
    void pushBackVariation(const char*, const char*);
    void calcCompileSource(ShaderType, sead::BufferedSafeString*, Target, bool);
    const sead::SafeString& getRegitserUniformBlockName();  // "RegisterUBO"

private:
    void* _8;
    const char* mName;
    void* _18;
    void* _20;
    sead::PtrArray<const char*> _28;
    sead::PtrArray<const char*> _38;
    sead::PtrArray<const char*> _48;
    sead::PtrArray<const char*> _58;
};

}  // namespace agl
