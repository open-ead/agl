#pragma once

#include <heap/seadDisposer.h>
#include <hostio/seadHostIONode.h>
#include <prim/seadSafeString.h>

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

    private:
        u32 mArg;
    };

    class DialogArg {
    public:
        DialogArg();

    private:
        u64* _0;
        u64* _8;
        void* _10;
        void* _18;
        void* _20;
        const char* mMsg;
        u64* _30;
        u64* _38;
        void* _40;
        u32 _48;  // set to 0x20
        u8 _4c;
        u8 _4d;
        u8 _4e;
        u8 _4f;
        u32 _50;
    };

    FileIOMgr();

    void initialize(const FileIOMgr::CreateArg& create_arg, sead::Heap* heap);
    void setCheckoutCommandPath(const sead::SafeString& path);
    void save(const sead::XmlDocument& document, const FileIOMgr::DialogArg& dialog_arg,
              u32 buffer_size);
    void showDialog(sead::hostio::FileInfo* file_info, const sead::SafeString& mode,
                    const sead::SafeString& id1, const sead::SafeString& id2_or_filter,
                    const sead::SafeString& file_name) const;
    void checkout_(const sead::SafeString& arg) const;
    void showErrorDialog_(const sead::SafeString& file) const;
    void save(const void* data, u32 size, const FileIOMgr::DialogArg& dialog_arg);
    s32 load(const FileIOMgr::DialogArg& dialog_arg);
    void close(s32 handle_index);
    void genMessage(sead::hostio::Context* unused);
    void listenPropertyEvent(const sead::hostio::PropertyEvent* unused);

private:
    sead::NinHostIOFileDevice* _28;
};

}  // namespace agl::detail
