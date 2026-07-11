#include "utility/aglParameter.h"

namespace agl::utl {

template bool ParameterCurve<1>::copy(const ParameterBase&);
template ParameterBase* ParameterCurve<1>::clone(sead::Heap*, IParameterObj*) const;

}  // namespace agl::utl
