#pragma once

#include <heap/seadDisposer.h>
#include <hostio/seadHostIONode.h>
#include <nvn/nvn.h>
#include "driver/aglGraphicsDriverMgr.h"

namespace agl::driver {

class NVNMgr : public GraphicsDriverMgr {
public:
    static NVNMgr* instance() { return (NVNMgr*)GraphicsDriverMgr::instance(); }
    static NVNMgr* createInstance(sead::Heap* heap);

    NVNdevice* getDevice() const { return mDevice; }

    NVNMgr();
    ~NVNMgr() override;

    NVNMgr(const NVNMgr&) = delete;
    NVNMgr& operator=(const NVNMgr&) = delete;
    NVNMgr(NVNMgr&&) = delete;
    NVNMgr& operator=(NVNMgr&&) = delete;

private:
    NVNdevice* mDevice;
    u8 mUnknown[0x470];
};

static_assert(sizeof(NVNMgr) == 0x4B0);

}  // namespace agl::driver
