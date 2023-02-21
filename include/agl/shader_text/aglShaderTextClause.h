#pragma once

#include <prim/seadSafeString.h>

namespace agl::shtxt {

class Clause {
public:
    class TableChecker {
    public:
        TableChecker();
    };

    using Type = u8;

    Clause();
    Clause(Clause::Type, const char*, const char*);
    ~Clause();

    u64 findNumberBlock(Clause::Type*, const char*);
    void appendTo(sead::BufferedSafeString*) const;
    void appendTo(sead::BufferedSafeString*, u32) const;
    void copyTo(sead::BufferedSafeString*) const;
    f64 toNumber() const;
    f64 forceNumber() const;
    u32 calcLineFeedCount() const;
    bool compareImpl(const Clause&, u32, const Clause*, const Clause*) const;
    bool compare(const sead::SafeString&, u32) const;
    bool compare(const Clause&, u32) const;
    s32 calcHash(const void*, u32, u32) const;

private:
    Clause* _0;
    Clause* _8;
    u8 mClauseType;
    u8 _11;
    u8 _12;
    u8 _13;
    u32 _14;
    char* _18;
    char* _20;

    static bool cTableChecked;
    static u32* cHashTable;
};

}  // namespace agl::shtxt
