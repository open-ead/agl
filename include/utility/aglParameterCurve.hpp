#pragma once

#include <aglVersion.h>

#ifndef AGL_UTILS_PARAMETER_H_
#include "utility/aglParameter.h"
#endif

namespace agl::utl {

template <u32 N>
inline ParameterCurve<N>::ParameterCurve(const sead::SafeString& name,
                                         const sead::SafeString& label, IParameterObj* param_obj)
    : ParameterBase(name, label, param_obj) {
    reset();
}

// NOTE: This is a hack to match ParameterBase::createByTypeName. It doesn't inline using the
// general template.
template <>
inline void ParameterCurve<4>::reset() {
    static f32 s_initialize[9] = {0.0, 0.0, 0.5, 0.5, 0.5, 0.5, 1.0, 1.0, 0.5};
    for (u32 i = 0; i < 4; ++i) {
        sead::MemUtil::copy(mCurveData[i].f, s_initialize, sizeof(s_initialize));
        for (u32 j = 9; j < cUnitCurveParamNum; ++j)
            mCurveData[i].f[j] = 1.0;
        mCurves[i].setData(&mCurveData[i], sead::hostio::CurveType::Hermit2D, cUnitCurveParamNum,
                           9);
    }
}

template <>
__attribute__((noinline, used)) inline void ParameterCurve<3>::reset() {
    static f32 s_initialize[9] = {0.0, 0.0, 0.5, 0.5, 0.5, 0.5, 1.0, 1.0, 0.5};

    sead::MemUtil::copy(mCurveData[0].f, s_initialize, sizeof(s_initialize));
    for (u32 j = 9; j < cUnitCurveParamNum; ++j)
        mCurveData[0].f[j] = 1.0;
    mCurves[0].setData(&mCurveData[0], sead::hostio::CurveType::Hermit2D, cUnitCurveParamNum, 9);

    sead::MemUtil::copy(mCurveData[1].f, s_initialize, sizeof(s_initialize));
    for (u32 j = 9; j < cUnitCurveParamNum; ++j)
        mCurveData[1].f[j] = 1.0;
    mCurves[1].setData(&mCurveData[1], sead::hostio::CurveType::Hermit2D, cUnitCurveParamNum, 9);

    sead::MemUtil::copy(mCurveData[2].f, s_initialize, sizeof(s_initialize));
    for (u32 j = 9; j < cUnitCurveParamNum; ++j)
        mCurveData[2].f[j] = 1.0;
    mCurves[2].setData(&mCurveData[2], sead::hostio::CurveType::Hermit2D, cUnitCurveParamNum, 9);
}

template <u32 N>
inline void ParameterCurve<N>::reset() {
    static f32 s_initialize[9] = {0.0, 0.0, 0.5, 0.5, 0.5, 0.5, 1.0, 1.0, 0.5};
    for (u32 i = 0; i < N; ++i) {
        sead::MemUtil::copy(mCurveData[i].f, s_initialize, sizeof(s_initialize));
        for (u32 j = 9; j < cUnitCurveParamNum; ++j)
            mCurveData[i].f[j] = 1.0;
        mCurves[i].setData(&mCurveData[i], sead::hostio::CurveType::Hermit2D, cUnitCurveParamNum,
                           9);
    }
}

template <u32 N>
inline bool ParameterCurve<N>::copy(const ParameterBase& other) {
    if (getParameterType() != other.getParameterType())
        return false;

    if (getName() != other.getName())
        return false;

    copyUnsafe(other);
    return true;
}

template <u32 N>
inline void ParameterCurve<N>::copyUnsafe(const ParameterBase& other) {
    if (getParameterType() != other.getParameterType()) {
        SEAD_ASSERT_MSG(false, "getParameterType() == src.getParameterType()");
        return;
    }

    sead::MemUtil::copy(ptr(), other.ptr(), size());
    for (u32 i = 0; i < N; ++i) {
        auto& curve = mCurves[i];
        auto& curve_other = static_cast<const ParameterCurve<N>&>(other).mCurves[i];
        curve.setCurveType(curve_other.getCurveType());
        curve.mInfo.numUse = curve_other.mInfo.numUse;
    }
}

template <u32 N>
inline ParameterType ParameterCurve<N>::getParameterType() const {
    if constexpr (N == 1)
        return ParameterType::Curve1;
    else if constexpr (N == 2)
        return ParameterType::Curve2;
    else if constexpr (N == 3)
        return ParameterType::Curve3;
    else if constexpr (N == 4)
        return ParameterType::Curve4;
    else
        static_assert(N == 1, "Invalid number of curves");
}

template <u32 N>
inline ParameterBase* ParameterCurve<N>::clone(sead::Heap* heap, IParameterObj* obj) const {
    auto* instance = new (heap) ParameterCurve<N>(getParameterName(), getLabel(), obj);
    sead::MemUtil::copy(instance->mCurveData.data(), mCurveData.data(), sizeof(mCurveData));
    return instance;
}

template <u32 N>
inline void ParameterCurve<N>::postApplyResource_(const void*, size_t size) {
    if (this->size() == size) {
        if constexpr (N == 3) {
            for (u32 i = 0; i < 2; ++i) {
                auto& curve = mCurves[i];
                auto& data = mCurveData[i];
                const auto type = sead::hostio::CurveType(data.curveType);
                curve.setCurveType(type);
                auto* floats = data.f;
                curve.setNumUse(data.numUse);
                curve.mFloats = floats;
                curve.mInfo.numFloats = cUnitCurveParamNum;
            }
            auto& curve = mCurves[2];
            auto& data = mCurveData[2];
            auto* floats = data.f;
            const auto type = sead::hostio::CurveType(data.curveType);
            curve.setCurveType(type);
            curve.mFloats = floats;
            curve.setNumUse(data.numUse);
            curve.mInfo.numFloats = cUnitCurveParamNum;
        } else {
            for (u32 i = 0; i < N; ++i) {
                auto& curve = mCurves[i];
                auto& data = mCurveData[i];
                if constexpr (N == 1) {
                    mCurves[i].setCurveType(sead::hostio::CurveType(mCurveData[i].curveType));
#if AGL_VERSION == AGL_VERSION_BOTW
                    mCurves[i].mFloats = mCurveData[i].f;
                    mCurves[i].mInfo.numFloats = cUnitCurveParamNum;
                    mCurves[i].setNumUse(mCurveData[i].numUse);
#else
                    mCurves[i].setNumUse(mCurveData[i].numUse);
                    mCurves[i].setFloats(&mCurveData[i], cUnitCurveParamNum);
#endif
                } else {
                    auto* floats = data.f;
                    const auto type = sead::hostio::CurveType(data.curveType);
                    curve.mInfo.curveType = u8(type);
                    curve.mInfo.numFloats = cUnitCurveParamNum;
                    curve.mFloats = floats;
                    const u32 num_use = data.numUse;
                    curve.mInfo.numUse = u8(num_use);
                }
            }
        }
    } else {
        if constexpr (N == 1) {
            for (u32 i = 0; i < N; ++i) {
                mCurves[i].mInfo.numFloats = cUnitCurveParamNum;
                mCurves[i].mFloats = mCurveData[i].f;
            }
        } else if constexpr (N == 2) {
            mCurves[0].mInfo.numFloats = cUnitCurveParamNum;
            mCurves[0].mFloats = mCurveData[0].f;
            mCurves[1].mFloats = mCurveData[1].f;
            mCurves[1].mInfo.numFloats = cUnitCurveParamNum;
        } else if constexpr (N == 3) {
            auto* floats0 = mCurveData[0].f;
            mCurves[0].mInfo.numFloats = cUnitCurveParamNum;
            auto* floats1 = mCurveData[1].f;
            mCurves[0].mFloats = floats0;
            auto* floats2 = mCurveData[2].f;
            mCurves[1].mInfo.numFloats = cUnitCurveParamNum;
            mCurves[1].mFloats = floats1;
            mCurves[2].mInfo.numFloats = cUnitCurveParamNum;
            mCurves[2].mFloats = floats2;
        } else if constexpr (N == 4) {
            mCurves[0].mInfo.numFloats = cUnitCurveParamNum;
            mCurves[0].mFloats = mCurveData[0].f;
            auto* floats1 = mCurveData[1].f;
            mCurves[1].mInfo.numFloats = cUnitCurveParamNum;
            mCurves[1].mFloats = floats1;
            mCurves[2].mFloats = mCurveData[2].f;
            mCurves[2].mInfo.numFloats = cUnitCurveParamNum;
            auto* floats3 = mCurveData[3].f;
            mCurves[3].mInfo.numFloats = cUnitCurveParamNum;
            mCurves[3].mFloats = floats3;
        } else {
            for (u32 i = 0; i < N; ++i) {
                mCurves[i].mFloats = mCurveData[i].f;
                mCurves[i].mInfo.numFloats = cUnitCurveParamNum;
            }
        }
    }
}

}  // namespace agl::utl
