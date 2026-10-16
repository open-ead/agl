#pragma once

#include <nvn/nvn.h>

#include <container/seadBuffer.h>
#include <heap/seadDisposer.h>
#include <hostio/seadHostIONode.h>
#include <thread/seadCriticalSection.h>

#include "common/aglDisplayList.h"
#include "common/aglShaderEnum.h"
#include "driver/aglGraphicsDriverMgr.h"

namespace agl::driver {

class NVNMgr : public GraphicsDriverMgr {
public:
    static NVNMgr* createInstance(sead::Heap* heap);
    static NVNMgr* instance() { return static_cast<NVNMgr*>(GraphicsDriverMgr::instance()); }

    NVNMgr();
    ~NVNMgr() override;

    static NVNshaderStage getNVNshaderStage(ShaderType type);

    NVNdevice* getNVNdevice() const { return mNVNdevice; }

private:
    NVNdevice* mNVNdevice;
    u8 _40[0x18];

    sead::CriticalSection _58;
    sead::CriticalSection _98;
    sead::CriticalSection _d8;
    sead::CriticalSection _118;
    u8 _158[0x48];

    DisplayList mDisplayList;
    u8 _400[0x38];

    sead::FixedSafeString<64> _438;
    u8 _490[0xb8];
};

static_assert(sizeof(NVNMgr) == 0x548);

}  // namespace agl::driver
