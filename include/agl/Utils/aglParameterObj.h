#pragma once

#include <hostio/seadHostIOReflexible.h>
#include <prim/seadSafeString.h>
#include "agl/Utils/aglResParameter.h"

namespace sead {
class XmlElement;
}

namespace agl::utl {

class IParameterList;
class ParameterBase;

class IParameterObj {
public:
    IParameterObj();
    virtual ~IParameterObj();

    void pushBackListNode(ParameterBase* param);
    void sortByHash();

    void createAttribute(sead::XmlElement* element, sead::Heap* heap) const;
    sead::SafeString getTagName();
    sead::SafeString getParameterObjName() const;

    void writeToXML(sead::XmlElement* element, sead::Heap* heap);
    bool readFromXML(const sead::XmlElement& element, bool x);

    void applyResParameterObj(ResParameterObj obj1, ResParameterObj obj2, f32 t,
                              IParameterList* list);
    bool isComplete(ResParameterObj obj, bool) const;
    void verify() const;
    void verify(ParameterBase* param1, ParameterBase* param2) const;

    bool copy(ParameterBase* param1, ParameterBase* param2, const ParameterBase* param3,
              const ParameterBase* param4);
    bool copy(const IParameterObj& obj);
    bool copyLerp(ParameterBase* param1, ParameterBase* param2, const ParameterBase* param3,
                  const ParameterBase* param4, f32 t);

#ifdef SEAD_DEBUG
    void genMessageParameter(sead::hostio::Context* context);
    void listenPropertyEventParameter(sead::hostio::Reflexible* reflexible,
                                      const sead::hostio::PropertyEvent* event);
#endif

protected:
    friend class IParameterList;

    virtual bool preWrite_() const { return true; }
    virtual void postWrite_() const {}
    virtual bool preRead_() { return true; }
    virtual void postRead_() {}
    virtual bool preCopy_() { return true; }
    virtual void postCopy_() {}
    virtual bool isApply_(ResParameterObj obj) const;

    void applyResParameterObj_(bool, ResParameterObjData obj1, ResParameterObj obj2, f32 t,
                               IParameterList* list);
    ParameterBase* searchParameter_(u32 hash);
    const ParameterBase* searchParameter_(u32 hash) const;

    bool copy_(ParameterBase* param1, ParameterBase* param2, const ParameterBase* param3,
               const ParameterBase* param4);
    bool copyLerp_(ParameterBase* param1, ParameterBase* param2, const ParameterBase* param3,
                   const ParameterBase* param4, f32 t);

    ParameterBase* mParam;
    void* _10;
    u32 _18;
    u32 mNameHash;
    void* _20;
    void* _28;
};

}  // namespace agl::utl
