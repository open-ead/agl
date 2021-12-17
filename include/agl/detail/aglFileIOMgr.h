#pragma once

#include <heap/seadDisposer.h>
#include <hostio/seadHostIONode.h>
#include <prim/seadSafeString.h>
#include "agl/Utils/aglParameterIO.h"

namespace sead {
namespace hostio {
class FileInfo;
}
class Heap;
class NinHostIOFileDevice;
class XmlDocument;
}  // namespace sead

namespace agl::detail {
class FileIOMgr : public sead::hostio::Node {
    SEAD_SINGLETON_DISPOSER(FileIOMgr)
public:
    class CreateArg {
    public:
        CreateArg();

        u32 mArg;  // _0
    };

    class DialogArg {
    public:
        DialogArg();

        u64* _0;
        u64* _8;
        u64 _10;
        u64 _18;
        u64 _20;
        char* mMsg;
        u64* _30;
        u64* _38;
        u64 _40;
        u32 _48;  // set to 0x20
        u8 _4c;
        u8 _4d;
        u8 _4e;
        u8 _4f;
        u32 _50;
    };

    FileIOMgr();

    void initialize(const agl::detail::FileIOMgr::CreateArg&, sead::Heap*);
    void setCheckoutCommandPath(const sead::SafeString&);
    void save(const sead::XmlDocument&, const agl::detail::FileIOMgr::DialogArg&, u32);
    void showDialog(sead::hostio::FileInfo*, const sead::SafeString&, const sead::SafeString&,
                    const sead::SafeString&, const sead::SafeString&) const;
    void checkout_(const sead::SafeString&) const;
    void showErrorDialog_(const sead::SafeString&) const;
    void save(void const*, u32, const agl::detail::FileIOMgr::DialogArg&);
    s32 load(const agl::detail::FileIOMgr::DialogArg&);
    void close(s32);
    void genMessage(sead::hostio::Context*);
    void listenPropertyEvent(sead::hostio::PropertyEvent const*);

private:
    sead::NinHostIOFileDevice* _28;
};
}  // namespace agl::detail
