#pragma once

#include "common/aglResCommon.h"
#include "common/aglShaderEnum.h"

namespace agl {

struct ResShaderBinaryData {
    u32 mSize;
    u32 mShaderType;
    s32 mDataOffset;  // Relative to end of struct
    u32 mDataSize;
};
static_assert(sizeof(ResShaderBinaryData) == 0x10, "agl::ResShaderBinaryData size mismatch");

class ResShaderBinary : public ResCommon<ResShaderBinaryData> {
public:
    using ResCommon::ResCommon;

    ShaderType getShaderType() const { return ShaderType(ref().mShaderType); }

    void* getData() const {
        const DataType* const data = ptr();
        return (void*)((uintptr_t)(data + 1) + data->mDataOffset);
    }

    void modifyBinaryEndian();
    void setUp();
};

using ResShaderBinaryArray = ResArray<ResShaderBinary>;

using ResShaderBinaryArrayData = ResShaderBinaryArray::DataType;
static_assert(sizeof(ResShaderBinaryArrayData) == 8, "agl::ResShaderBinaryArrayData size mismatch");

}  // namespace agl
