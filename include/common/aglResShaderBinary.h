#pragma once

#include "common/aglResCommon.h"
#include "common/aglShaderEnum.h"

namespace agl {

#pragma pack(push, 4)
template <typename T>
union ResShaderBinaryPtr {
    s32 mOffset;
    T* mPtr;
};

template <u32 Size>
struct ResShaderBinaryPtrEntry {
    ResShaderBinaryPtr<const void> mValue;
    u8 mPadding[Size - sizeof(mValue)];
};

using ResShaderBinaryPtrEntry16 = ResShaderBinaryPtrEntry<0x10>;
using ResShaderBinaryPtrEntry12 = ResShaderBinaryPtrEntry<0xC>;

struct ResShaderBinaryNvnData {
    u8 mUnknown00[0xC];
    ResShaderBinaryPtr<void> mData;
    u32 mEntry16ANum;
    ResShaderBinaryPtr<ResShaderBinaryPtrEntry16> mEntry16A;
    u32 mEntry16BNum;
    ResShaderBinaryPtr<ResShaderBinaryPtrEntry16> mEntry16B;
    u32 mEntry12ANum;
    ResShaderBinaryPtr<ResShaderBinaryPtrEntry12> mEntry12A;
    u32 mEntry12BNum;
    ResShaderBinaryPtr<ResShaderBinaryPtrEntry12> mEntry12B;
    u32 mEntry12CNum;
    ResShaderBinaryPtr<ResShaderBinaryPtrEntry12> mEntry12C;
    u32 mEntry12DNum;
    ResShaderBinaryPtr<ResShaderBinaryPtrEntry12> mEntry12D;
};
#pragma pack(pop)

static_assert(sizeof(ResShaderBinaryNvnData) == 0x5C);

struct ResShaderBinaryData {
    s32 mSize;
    u32 mShaderType;
    s32 mDataOffset;  // Relative to end of struct
    u32 mDataSize;
};

class ResShaderBinary : public ResCommon<ResShaderBinaryData> {
public:
    using ResCommon::ResCommon;

    ShaderType getShaderType() const { return ShaderType(ref().mShaderType); }

    void* getData() const {
        const DataType* const data = ptr();
        return (void*)((uintptr_t)(data + 1) + data->mDataOffset);
    }

    void modifyBinaryEndian();
    void resolvePtr(const void* base);
    void setUp();
};

using ResShaderBinaryArray = ResArray<ResShaderBinary>;

using ResShaderBinaryArrayData = ResShaderBinaryArray::DataType;

}  // namespace agl
