#pragma once

#include <container/seadPtrArray.h>
#include <heap/seadDisposer.h>
#include <hostio/seadHostIOReflexible.h>
#include <prim/seadSafeString.h>
#include <resource/seadArchiveRes.h>
#include "agl/common/aglShaderProgramArchive.h"

namespace agl {

class ShaderProgram;

namespace detail {

class ShaderHolder {
    SEAD_SINGLETON_DISPOSER(ShaderHolder);

public:
    ShaderHolder();
    virtual ~ShaderHolder();

    void initialize(sead::ArchiveRes* archiveRes, sead::Heap* heap);
    sead::FormatFixedSafeString<1024> genMessage(sead::hostio::Context* context);
    void listenPropertyEvent(const sead::hostio::PropertyEvent* property_event);

private:
    sead::PtrArray<ShaderProgram> mShaderPrograms;
    ShaderProgram* mShaderProgramsBuffer[206];
    ShaderProgramArchive mShaderProgramArchives[6];
    char mArchiveOptions;
};
static_assert(sizeof(ShaderHolder) == 0xB30);

}  // namespace detail
}  // namespace agl
