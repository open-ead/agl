#pragma once

#include <container/seadPtrArray.h>
#include <heap/seadDisposer.h>
#include <hostio/seadHostIOReflexible.h>
#include <prim/seadSafeString.h>
#include <resource/seadArchiveRes.h>
#include "common/aglShaderProgramArchive.h"

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
    sead::FixedPtrArray<ShaderProgram, 206> mShaderPrograms;
    sead::UnsafeArray<ShaderProgramArchive, 6> mShaderProgramArchives;
    bool mArchiveOptions;
};
static_assert(sizeof(ShaderHolder) == 0xB30);

}  // namespace detail
}  // namespace agl
