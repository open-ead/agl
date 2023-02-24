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
    bool set(sead::Heap*, const Clause*, const Clause*);
    bool setImpl(sead::Heap*, const Clause*, const Clause*, bool);
    void setDirect(Clause*, u32, bool);
    void updateHash();
    void replace(sead::Heap*, const Clause*, const Clause*, bool);
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
    s16 _44;   // -1
    bool _46;  // 1
    bool _47;  // 1
};
static_assert(sizeof(DefineLinker) == 0x48);

}  // namespace agl::shtxt
