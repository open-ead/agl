#pragma once

#include "common/aglResShaderMacro.h"
#include "common/aglResShaderSymbol.h"
#include "common/aglResShaderVariation.h"

namespace agl {

struct ResShaderProgramData {
    u32 mSize;
    u32 mNameLen;
    s32 mSourceIndex[cShaderType_Num];
    // char mName[];
};
#ifdef SWITCH
static_assert(sizeof(ResShaderProgramData) == 0x18, "agl::ResShaderProgramData size mismatch");
#endif
#ifdef cafe
static_assert(sizeof(ResShaderProgramData) == 0x14, "agl::ResShaderProgramData size mismatch");
#endif

class ResShaderProgram : public ResCommon<ResShaderProgramData> {
public:
    using ResCommon::ResCommon;

    const char* getName() const { return (const char*)(ptr() + 1); }

    ResShaderMacroArray getResShaderMacroArray(ShaderType type) const;

    ResShaderVariationArray getResShaderVariationArray() const;

    ResShaderVariationArray getResShaderVariationDefaultArray() const {
        return (const ResShaderVariationArrayData*)((uintptr_t)getResShaderVariationArray().ptr() +
                                                    getResShaderVariationArray().ref().mSize);
    }

    ResShaderSymbolArray getResShaderSymbolArray(ShaderSymbolType type) const;
};

using ResShaderProgramArray = ResArray<ResShaderProgram>;

using ResShaderProgramArrayData = ResShaderProgramArray::DataType;
static_assert(sizeof(ResShaderProgramArrayData) == 8,
              "agl::ResShaderProgramArrayData size mismatch");

}  // namespace agl
