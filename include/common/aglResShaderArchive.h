#pragma once

#include "common/aglResCommon.h"
#include "common/aglResShaderProgram.h"
#include "common/aglResShaderSource.h"

namespace agl {

struct ResShaderArchiveData {
    union {
        char mSignature[4];
        u32 mSigWord;
    };
    u32 mVersion;
    u32 mFileSize;
    u32 mEndian;
    u32 mNameLen;
    // char mName[];

public:
    static u32 getVersion();
    static u32 getSignature();
    static const char* getExtension();

private:
    static const u32 cVersion = 11;
    static const u32 cSignature = 0x53484141;  // SHAA
#ifdef cafe
    static const u32 cEndianCheckBit = 0x01000001;
#endif
#ifdef SWITCH
    static const u32 cEndianCheckBit = 0x00000001;
#endif

    friend class ResCommon<ResShaderArchiveData>;
    friend class ResShaderArchive;
};
static_assert(sizeof(ResShaderArchiveData) == 0x14, "agl::ResShaderArchiveData size mismatch");

class ResShaderArchive : public ResCommon<ResShaderArchiveData> {
    AGL_RES_FILE_HEADER()

public:
    using ResCommon::ResCommon;

    const char* getName() const {
        const DataType* const data = ptr();
        return (const char*)(data + 1);
    }

    ResShaderProgramArray getResShaderProgramArray() const {
        const DataType* const data = ptr();
        return (const ResShaderProgramArrayData*)((uintptr_t)(data + 1) + data->mNameLen);
    }

    s32 getResShaderProgramNum() const { return getResShaderProgramArray().getNum(); }

    ResShaderSourceArray getResShaderSourceArray() const {
        const ResShaderProgramArrayData* const data = getResShaderProgramArray().ptr();
        return (const ResShaderSourceArrayData*)((uintptr_t)data + data->mSize);
    }

    s32 getResShaderSourceNum() const { return getResShaderSourceArray().getNum(); }

    bool setUp();
};

}  // namespace agl
