#pragma once

#include "common/aglResBinaryShaderProgram.h"
#include "common/aglResShaderBinary.h"
#include "common/aglResShaderProgram.h"
#include <nvn/nvn.h>

namespace agl {

struct ResBinaryShaderArchiveData {
    union {
        char mSignature[4];
        u32 mSigWord;
    };
    u32 mVersion;
    u32 mFileSize;
    u32 mEndian;
    u32 mUnknown10;
    u32 mNameLen;
    u32 mMemoryPoolSize;
    u32 mMemoryPoolOffset;
    NVNmemoryPool mMemoryPool;
    NVNbuffer mBuffer;
    // char mName[];

public:
    static u32 getVersion();
    static u32 getSignature();
    static const char* getExtension();

private:
    static const u32 cVersion = 9;
    static const u32 cSignature = 0x53484142;  // SHAB
    static const u32 cEndianCheckBit = 0x01000001;

    friend class ResCommon<ResBinaryShaderArchiveData>;
    friend class ResBinaryShaderArchive;
};
static_assert(sizeof(ResBinaryShaderArchiveData) == 0x150,
              "agl::ResBinaryShaderArchiveData size mismatch");

class ResBinaryShaderArchive : public ResCommon<ResBinaryShaderArchiveData> {
    AGL_RES_FILE_HEADER()

public:
    using ResCommon::ResCommon;

    const char* getName() const {
        const DataType* const data = ptr();
        return (const char*)(data + 1);
    }

    ResShaderBinaryArray getResShaderBinaryArray() const {
        const DataType* const data = ptr();
        uintptr_t offset = data->mNameLen;
        offset += (uintptr_t)data;
        return (const ResShaderBinaryArrayData*)(offset + sizeof(DataType));
    }

    s32 getResShaderBinaryNum() const { return getResShaderBinaryArray().getNum(); }

    ResBinaryShaderProgramArray getResBinaryShaderProgramArray() const {
        const ResShaderBinaryArrayData* const data = getResShaderBinaryArray().ptr();
        return (const ResBinaryShaderProgramArrayData*)((uintptr_t)data + (u32)data->mSize);
    }

    s32 getResBinaryShaderProgramNum() const { return getResBinaryShaderProgramArray().getNum(); }

    bool setUp(bool le_resolve_pointers);

private:
    void createMemoryPoolBuffer_();
};

}  // namespace agl
