#pragma once

#include <prim/seadSafeString.h>
#include "agl/detail/aglSurface.h"
#include "agl/driver/aglNVNtexture.h"

namespace agl {
class TextureData {
public:
    class CompressToWork {
    public:
        explicit CompressToWork(const TextureData&);

        u64 _0;
        u64 _8;
        u64 _10;
        u64 _18;
        u32 _20;
        u64 _28;
        u64 _30;
        u32 _38;
        u64 _40;
        detail::Surface mSurface;
        driver::NVNtexture_ mTexture;
    };

    TextureData();

    void setMipLevelNum_(s32, bool);
    u16 getMinSlice_() const;
    void getTextureFormatName() const;
    u32 calcMipByteSize(u32) const;
    bool isCompressedFormat() const;
    bool isRenderTargetCompressAvailable() const;
    bool isDepthFormat() const;
    bool hasStencil() const;
    void invalidateCPUCache();
    void flushCPUCache() const;
    void setDebugLabel(const sead::SafeString&);
    void getDebugLabel() const;

private:
    u64 _0;
    u32 _8;
    u32 _c;
    u64 _10;
    u64 _18;
    u64 _20;
    u64 _28;
    detail::Surface mSurface;
    TextureFormat mTextureFormat;
    u8 _58[0x120 - 0x58];
    const char* _120;  // "agl::TextureData string"
};
}  // namespace agl
