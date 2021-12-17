#pragma once

#include <prim/seadSafeString.h>

namespace sead {
class Heap;
class ExpHeap;
}  // namespace sead

namespace agl::shtxt {
class Clause;
class DefineLinker;
class MacroDeployInfo;
class MacroReplaceInfo;

class Preprocessor {
public:
    Preprocessor(sead::Heap*, sead::Heap*);
    ~Preprocessor();

    void finalize();
    void initialize(const char*);
    void removeClause(agl::shtxt::Clause*) const;
    void removeClause(agl::shtxt::Clause*, agl::shtxt::Clause*, bool) const;
    void removeClauseAll();
    void removeDefineLinkerAll();
    void setReplacedMacro(const char**, const char**, u32);
    void setDeployMacro(const char**, u32);
    void appendMacro(const agl::shtxt::DefineLinker*);
    bool preprocess(u32, u64, u64);
    void removeComment();
    void forceLF();
    void reduceSpace();
    void reduceLF();
    void format(bool);
    bool construct(sead::BufferedSafeString* dest) const;
    u64 calcConstructLength() const;

    u64 _0;
    u64 _8;  // some sort of size
    u64 _10;
    sead::ExpHeap* _18;
    u64 _20;
    agl::shtxt::Clause* _28;
    agl::shtxt::DefineLinker* _30;
    char* mRefName;
    agl::shtxt::MacroReplaceInfo* _40;
    u32 _48;  // related to replace info
    u32 _4c;
    agl::shtxt::MacroDeployInfo* _50;
    u32 _58;  // related to deploy info
    u32 _5c;
    agl::shtxt::DefineLinker* _60;
    u64 _68;
};
}  // namespace agl::shtxt
