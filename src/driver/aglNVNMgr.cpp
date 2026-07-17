#include "driver/aglNVNMgr.h"

namespace agl::driver {

NVNMgr* NVNMgr::createInstance(sead::Heap* heap)
{
    NVNMgr* instance = (NVNMgr*)GraphicsDriverMgr::sInstance;
    if (!instance)
    {
        u8* buffer = new (heap, alignof(NVNMgr)) u8[sizeof(NVNMgr)];
        instance = (NVNMgr*)buffer;
        GraphicsDriverMgr::SingletonDisposer_::sStaticDisposer =
            new (&instance->mSingletonDisposerBuf_) GraphicsDriverMgr::SingletonDisposer_(heap);
        instance = new (instance) NVNMgr;
        GraphicsDriverMgr::sInstance = instance;
    }
    return instance;
}

}  // namespace agl::driver
