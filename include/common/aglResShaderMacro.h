#pragma once

#include "common/aglResCommon.h"

namespace agl {

struct ResShaderMacroData {
    u32 mSize;
    u32 mNameLen;
    u32 mValueLen;
    // char mName[];
};
static_assert(sizeof(ResShaderMacroData) == 0xC, "agl::ResShaderMacroData size mismatch");

class ResShaderMacro : public ResCommon<ResShaderMacroData> {
public:
    using ResCommon::ResCommon;

    const char* getName() const { return (const char*)(ptr() + 1); }

    const char* getValue() const { return getName() + ptr()->mNameLen; }
};

using ResShaderMacroArray = ResArray<ResShaderMacro>;

using ResShaderMacroArrayData = ResShaderMacroArray::DataType;
static_assert(sizeof(ResShaderMacroArrayData) == 8, "agl::ResShaderMacroArrayData size mismatch");

}  // namespace agl
