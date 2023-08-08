#pragma once

#include "common/aglResCommon.h"

namespace agl {

struct ResShaderVariationData {
    u32 mSize;
    u32 mNameLen;
    s32 mValueNum;
    u32 mIDLen;
    // char name[];
};
static_assert(sizeof(ResShaderVariationData) == 0x10, "agl::ResShaderVariationData size mismatch");

class ResShaderVariation : public ResCommon<ResShaderVariationData> {
public:
    using ResCommon::ResCommon;

    const char* getName() const { return (const char*)(ptr() + 1); }

    const char* getID() const;
    const char* getValue(s32 index) const;
};

using ResShaderVariationArray = ResArray<ResShaderVariation>;

using ResShaderVariationArrayData = ResShaderVariationArray::DataType;
static_assert(sizeof(ResShaderVariationArrayData) == 8,
              "agl::ResShaderVariationArrayData size mismatch");

}  // namespace agl
