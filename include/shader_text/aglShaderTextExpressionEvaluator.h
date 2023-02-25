#pragma once

#include <container/seadObjArray.h>

namespace sead {
class Heap;

template <typename T>
class AnyDelegate1Const;
}  // namespace sead

namespace agl::shtxt {

class Clause;
class SyntaxLeash;

class ExpressionEvaluator {
public:
    ExpressionEvaluator();
    ExpressionEvaluator(sead::Heap*, sead::Heap*, const sead::AnyDelegate1Const<Clause*>*);

    void initialize(sead::Heap*, sead::Heap*, const sead::AnyDelegate1Const<Clause*>*);
    u64 findSyntaxLeash(sead::ObjArray<SyntaxLeash>*, const Clause*) const;
    u64* createBinaryOperatorSyntaxTree(sead::ObjArray<SyntaxLeash>*, Clause*);
    u64* createTernaryOperatorSyntaxTree(sead::ObjArray<SyntaxLeash>*, Clause*);
    u64* createTokenOperatorSyntaxTree(sead::ObjArray<SyntaxLeash>*, Clause*);
    void resolveOperatorTokenConnect(sead::ObjArray<SyntaxLeash>*, Clause*, Clause*);
    void resolveOperatorUnary(sead::ObjArray<SyntaxLeash>*, Clause*, Clause*);
    void resolveOperatorMathHigh(sead::ObjArray<SyntaxLeash>*, Clause*, Clause*);
    void resolveOperatorMathLow(sead::ObjArray<SyntaxLeash>*, Clause*, Clause*);
    void resolveOperatorShift(sead::ObjArray<SyntaxLeash>*, Clause*, Clause*);
    void resolveOperatorCompareHigh(sead::ObjArray<SyntaxLeash>*, Clause*, Clause*);
    void resolveOperatorCompareLow(sead::ObjArray<SyntaxLeash>*, Clause*, Clause*);
    void resolveOperatorBitOpAnd(sead::ObjArray<SyntaxLeash>*, Clause*, Clause*);
    void resolveOperatorBitOpXor(sead::ObjArray<SyntaxLeash>*, Clause*, Clause*);
    void resolveOperatorBitOpOr(sead::ObjArray<SyntaxLeash>*, Clause*, Clause*);
    void resolveOperatorLogicalAnd(sead::ObjArray<SyntaxLeash>*, Clause*, Clause*);
    void resolveOperatorLogicalOr(sead::ObjArray<SyntaxLeash>*, Clause*, Clause*);
    void resolveOperatorTernary(sead::ObjArray<SyntaxLeash>*, Clause*, Clause*);
    void resolveOperatorAssignment(sead::ObjArray<SyntaxLeash>*, Clause*, Clause*);
    void resolveOperator(sead::ObjArray<SyntaxLeash>*, Clause*, Clause*);
    void resolveParenthesis(sead::ObjArray<SyntaxLeash>*, Clause*, Clause*);
    void resolve(Clause*, Clause*, bool);

private:
    sead::Heap* _0;
    sead::Heap* _8;
    sead::AnyDelegate1Const<Clause*>* _10;
};

}  // namespace agl::shtxt
