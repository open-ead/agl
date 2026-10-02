#pragma once

#include <prim/seadSafeString.h>
#include "detail/aglSurface.h"
#include "driver/aglNVNtexture.h"

namespace agl {

class TextureData {
public:
    class CompressToWork {
    public:
        explicit CompressToWork(const TextureData&);

        void* _0;
        void* _8;
        void* _10;
        void* _18;
        u32 _20;
        void* _28;
        void* _30;
        u32 _38;
        void* _40;
        detail::Surface mSurface;
        driver::NVNtexture_ mTexture;
    };

    // TODO: Rename parameters names
    static TextureData* create(TextureType type, TextureFormat format, u32 a, u32 b, u32 c, u32 d,
                               agl::TextureAttribute attribute,
                               agl::MultiSampleType multiSampleType, bool e) {
        agl::TextureData* textureData = new agl::TextureData();
        textureData->initialize_(type, format, a, b, c, d, attribute, multiSampleType, e);
        return textureData;
    }

    TextureData();

    void getTextureFormatName() const;
    u32 calcMipByteSize(u32) const;
    bool isCompressedFormat() const;
    bool isRenderTargetCompressAvailable() const;
    bool isDepthFormat() const;
    bool hasStencil() const;
    void invalidateCPUCache();
    void flushCPUCache() const;
    void setDebugLabel(const sead::SafeString& debug_label);
    void getDebugLabel() const;

    void* get_0() const { return _0; }

private:
    void initialize_(agl::TextureType, agl::TextureFormat, u32, u32, u32, u32,
                     agl::TextureAttribute, agl::MultiSampleType, bool);
    void setMipLevelNum_(s32, bool);
    u16 getMinSlice_() const;

    void* _0;
    u32 _8;
    u32 _c;
    void* _10;
    void* _18;
    void* _20;
    void* _28;
    detail::Surface mSurface;
    TextureFormat mTextureFormat;
    u8 _58[0x120 - 0x58];
    const char* mDebugLabel;  // "agl::TextureData string"
};

}  // namespace agl
