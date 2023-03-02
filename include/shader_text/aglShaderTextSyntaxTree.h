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
    explicit SyntaxTree(Clause*);
    ~SyntaxTree();

    void removeClauseRecursive(const sead::AnyDelegate1Const<Clause*>*);
    f64 checkAndGetValue();
    void checkAndEvaluate(const SyntaxTree*) const;
    f64 evaluate();
    void constructRecursive(sead::Heap*, sead::Heap*);
    u64* construct(sead::Heap*, sead::Heap*) const;

private:
    SyntaxTree* _0;
    SyntaxTree* _8;
    SyntaxTree* _10;
    void* _18;
    Clause* _20;
    void* _28;
    u32 _30;
};

}  // namespace agl::shtxt
