#include "agl/Utils/aglParameter.h"
#include <codec/seadHashCRC32.h>

namespace agl::utl {

u32 ParameterBase::calcHash(const sead::SafeString& key) {
    return sead::HashCRC32::calcStringHash(key.cstr());
}

}  // namespace agl::utl
