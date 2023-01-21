#pragma once

#include <basis/seadTypes.h>

namespace sead {
class Heap;
}

namespace agl::shtxt {

class Clause;

class Lexer {
public:
    Lexer();
    ~Lexer();

    void initialize(sead::Heap*, char const*, Clause*);
    void setupCurrentRange(u64 range);
    u32 findNumberBlock() const;
    Clause* createClause(u32) const;
    bool execute(bool);

private:
    sead::Heap* _0;
    Clause* _8;
    const char* mRefName;
    u64 _18;
    u64 _20;
    u64 _28;
};

}  // namespace agl::shtxt
