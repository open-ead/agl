#pragma once

#include <basis/seadTypes.h>

namespace sead {
class Heap;
}

namespace agl::shtxt {

class Clause;

class DefineLinker {
public:
    DefineLinker();
    ~DefineLinker();

    void clear();
    bool set(sead::Heap*, Clause const*, Clause const*);
    bool setImpl(sead::Heap*, Clause const*, Clause const*, bool);
    void setDirect(Clause*, u32, bool);
    void updateHash();
    void replace(sead::Heap*, Clause const*, Clause const*, bool);
    DefineLinker* clone(sead::Heap*, sead::Heap*) const;
    DefineLinker* cloneAll(sead::Heap*, sead::Heap*) const;

private:
    DefineLinker* _0;  // seems to copy itself twice
    DefineLinker* _8;
    Clause* _10;
    Clause* _18;  // hash clause?
    void* _20;
    Clause* _28;
    void* _30;
    void* _38;
    s32 mHash;
    s16 _44;  // -1
    u16 _46;  // 0x101
};

}  // namespace agl::shtxt
