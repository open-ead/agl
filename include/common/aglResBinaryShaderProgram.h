#pragma once

#include "common/aglResShaderSymbol.h"
#include "common/aglResShaderVariation.h"

namespace agl {

struct ResBinaryShaderProgramData {
    u32 mSize;
    u32 mNameLen;
    u32 mKind;
    u32 mBaseIndex;
    // char mName[];
};
static_assert(sizeof(ResBinaryShaderProgramData) == 0x10,
              "agl::ResBinaryShaderProgramData size mismatch");

class ResBinaryShaderProgram : public ResCommon<ResBinaryShaderProgramData> {
public:
    using ResCommon::ResCommon;

    const char* getName() const { return (const char*)(ptr() + 1); }

    ResShaderVariationArray getResShaderVariationArray() const {
        const DataType* const data = ptr();
        return (const ResShaderVariationArrayData*)((uintptr_t)(data + 1) + data->mNameLen);
    }

    ResShaderVariationArray getResShaderVariationDefaultArray() const {
        const ResShaderVariationArrayData* const data = getResShaderVariationArray().ptr();
        return (const ResShaderVariationArrayData*)((uintptr_t)data + data->mSize);
    }

    ResShaderSymbolArray getResShaderSymbolArray(ShaderSymbolType type) const;
};

using ResBinaryShaderProgramArray = ResArray<ResBinaryShaderProgram>;

using ResBinaryShaderProgramArrayData = ResBinaryShaderProgramArray::DataType;
static_assert(sizeof(ResBinaryShaderProgramArrayData) == 8,
              "agl::ResBinaryShaderProgramArrayData size mismatch");

}  // namespace agl
