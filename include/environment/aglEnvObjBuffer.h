#pragma once

#include <container/seadSafeArray.h>
#include "environment/aglEnvObj.h"

namespace agl::env {

// TODO
class EnvObjBuffer {
public:
    class AllocateArg {
    public:
        AllocateArg();
        virtual ~AllocateArg() = default;

        int getCount(int type) const { return mCounts[type]; }
        int getTotal() const { return mTotal; }

        void setContainMax(int type, int count);
        void setContainMax(const TypeInfo* type, int count) { setContainMax(type->id, count); }

    protected:
        sead::SafeArray<int, 0x80> mCounts;
        int mTotal = 0;
    };
};

}  // namespace agl::env
