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

    void initialize(sead::Heap*, const char*, Clause*);
    void setupCurrentRange(u64 range);
    u32 findNumberBlock() const;
    Clause* createClause(u32) const;
    bool execute(bool);

private:
    sead::Heap* _0;
    Clause* _8;
    const char* mRefName;
    void* _18;
    void* _20;
    void* _28;
};

}  // namespace agl::shtxt
