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
    void removeClause(Clause*) const;
    void removeClause(Clause*, Clause*, bool) const;
    void removeClauseAll();
    void removeDefineLinkerAll();
    void setReplacedMacro(const char**, const char**, u32);
    void setDeployMacro(const char**, u32);
    void appendMacro(const DefineLinker*);
    bool preprocess(u32, u64, u64);
    void removeComment();
    void forceLF();
    void reduceSpace();
    void reduceLF();
    void format(bool);
    bool construct(sead::BufferedSafeString* dest) const;
    u64 calcConstructLength() const;

private:
    void* _0;
    void* _8;  // some sort of size
    void* _10;
    sead::ExpHeap* _18;
    void* _20;
    Clause* _28;
    DefineLinker* _30;
    const char* mRefName;
    MacroReplaceInfo* _40;
    u32 _48;  // related to replace info
    u32 _4c;
    MacroDeployInfo* _50;
    u32 _58;  // related to deploy info
    u32 _5c;
    DefineLinker* _60;
    void* _68;
};

}  // namespace agl::shtxt
