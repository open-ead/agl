#pragma once

#include <basis/seadTypes.h>
#include <hostio/seadHostIOReflexible.h>
#include <prim/seadSafeString.h>
#include "agl/Utils/aglResParameter.h"

namespace sead {
class Heap;
class XmlElement;
}  // namespace sead

namespace agl::utl {

class IParameterObj;

class ParameterBase {
public:
    enum class ParameterType {
        Bool = 0,
        F32 = 1,
        Int = 2,
        Vec2 = 3,
        Vec3 = 4,
        Vec4 = 5,
        Color = 6,
        String32 = 7,
        String64 = 8,
        Curve1 = 9,
        Curve2 = 10,
        Curve3 = 11,
        Curve4 = 12,
        BufferInt = 13,
        BufferF32 = 14,
        String256 = 15,
        Quat = 16,
        U32 = 17,
        BufferU32 = 18,
        BufferBinary = 19,
        StringRef = 20,
        Special = 21,
    };

    ParameterBase();
    ParameterBase(const sead::SafeString& name, const sead::SafeString& label,
                  IParameterObj* param_obj);
    ParameterBase(const sead::SafeString& name, const sead::SafeString& label,
                  const sead::SafeString& meta, IParameterObj* param_obj);
    virtual ~ParameterBase() = default;

    void initializeListNode(const sead::SafeString& name, const sead::SafeString& label,
                            const sead::SafeString& meta, IParameterObj* param_obj);

    sead::SafeString getParameterName() const;
    sead::SafeString getLabel() const;
    sead::SafeString getMeta() const;

    static const char* getTagName();
    static const char* getAttributeNameString();
    static const char* getAttributeTypeString();
    static const char* getAttributeValueString();
    static const char* getParameterTypeName(ParameterType type);

    bool isSafeType(ParameterType type) const;
    bool verifyType(ParameterType type) const;

    virtual bool copy(const ParameterBase& other);
    virtual void copyUnsafe(const ParameterBase& other);
    virtual bool copyLerp(const ParameterBase& param1, const ParameterBase& param2, f32 t);

#ifdef SEAD_DEBUG
    virtual void genMessageParameter(sead::hostio::Context* context);
    void genMessageParameter(sead::hostio::Context* context, const sead::SafeString&);
    virtual void listenPropertyEventParameter(sead::hostio::Reflexible* reflexible,
                                              const sead::hostio::PropertyEvent* event);
#endif

    virtual void writeToXML(sead::XmlElement* element, sead::Heap* heap);
    virtual bool readFromXML(const sead::XmlElement& element, bool x);

    virtual ParameterType getParameterType() const = 0;
    virtual const void* ptr() const = 0;
    virtual void* ptr() = 0;
    virtual const void* typePtr() const = 0;
    virtual void* typePtr() = 0;
    virtual u32 size() const = 0;
    virtual u32 calcBinarizeSize() const { return size(); }
    virtual ParameterBase* clone(sead::Heap* heap, IParameterObj* obj) const = 0;

    void applyResource(ResParameter res);
    void applyResource(ResParameter res, f32 t);
    void applyString(const sead::SafeString& string, bool x);
    virtual void postApplyResource_(const void*, size_t) {}
    void createByTypeName(const sead::SafeString& a, const sead::SafeString& b);

    virtual bool isBinary() const { return false; }
    virtual bool isBinaryInternalBuffer() const { return true; }
    bool isInterpolatable() const;
    size_t binarize(void* binary) const;
    bool makeZero();

    static u32 calcHash(const sead::SafeString& key);

    template <typename T>
    T* ptrT() {
        return static_cast<T*>(ptr());
    }

    template <typename T>
    const T* ptrT() const {
        return static_cast<const T*>(ptr());
    }

protected:
    friend class IParameterObj;

    template <typename T>
    void copyLerp_(const ParameterBase& param1, const ParameterBase& param2, f32 t);

    u32 mNameHash;
    ParameterBase* mNext;

#ifdef SEAD_DEBUG
    const char* mName;
    const char* mLabel;
    const char* mMeta;
#endif
};

using ParameterType = ParameterBase::ParameterType;

}  // namespace agl::utl
