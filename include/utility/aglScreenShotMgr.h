#pragma once

#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>
#include "common/aglTextureDataSerializer.h"

namespace agl::utl {

// TODO
class ScreenShotMgr {
    SEAD_SINGLETON_DISPOSER(ScreenShotMgr)
    ScreenShotMgr() = default;
    virtual ~ScreenShotMgr();

public:
    void reserveCaptureWithDebugHeap(bool unk, agl::TextureDataSerializerTGA::TGAFormat format,
                                     const sead::SafeString&, bool unk2);
};

}  // namespace agl::utl
