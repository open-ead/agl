#pragma once

#include <basis/seadTypes.h>

namespace sead {
class Heap;

template <typename T>
class AnyDelegate1Const;
}  // namespace sead

namespace agl::shtxt {
class Clause;

class SyntaxTree {
public:
    SyntaxTree(Clause*);
    ~SyntaxTree();

    void removeClauseRecursive(sead::AnyDelegate1Const<Clause*> const*);
    f64 checkAndGetValue();
    void checkAndEvaluate(SyntaxTree const*) const;
    f64 evaluate();
    void constructRecursive(sead::Heap*, sead::Heap*);
    u64* construct(sead::Heap*, sead::Heap*) const;

private:
    SyntaxTree* _0;
    SyntaxTree* _8;
    SyntaxTree* _10;
    u64 _18;
    Clause* _20;
    u64 _28;
    u32 _30;
};
}  // namespace agl::shtxt
