#pragma once

#include <hostio/seadHostIOReflexible.h>
#include <prim/seadSafeString.h>
#include "agl/Utils/aglResParameter.h"

namespace sead {
class XmlElement;
}

namespace agl::utl {

class IParameterObj;
class ParameterBase;

class IParameterList {
public:
    IParameterList();
    virtual ~IParameterList();

    void addList(IParameterList* list, const sead::SafeString& name);
    void addObj(IParameterObj* obj, const sead::SafeString& name);
    void clearList();
    void clearObj();
    void removeList(IParameterList* list);
    void removeObj(IParameterObj* obj);

    void applyResParameterList(ResParameterList list);

    bool isComplete(ResParameterList res_list, bool) const;

    void createAttribute(sead::XmlElement* element, sead::Heap* heap) const;

    sead::SafeString getTagName();
    sead::SafeString getParameterListName() const;

    void writeToXML(sead::XmlElement* element, sead::Heap* heap);
    bool readFromXML(const sead::XmlElement& element, bool x);

    void verify() const;
    void verifyList() const;
    void verifyObj() const;
    void verifyObj(IParameterObj* obj1, IParameterObj* obj2) const;
    void verifyList(IParameterList* list1, IParameterList* list2) const;

    void sortByHash();

#ifdef SEAD_DEBUG
    void genMessageParameter(sead::hostio::Context* context);
    void listenPropertyEventParameter(sead::hostio::Reflexible* reflexible,
                                      const sead::hostio::PropertyEvent* event);
#endif

protected:
    virtual bool preWrite_() const { return true; }
    virtual void postWrite_() const {}
    virtual bool preRead_() { return true; }
    virtual void postRead_() {}
    virtual bool isApply_(ResParameterList list) const;
    virtual void callbackNotAppliable_(IParameterObj* obj, ParameterBase* param1,
                                       ResParameterObj res_obj);
    virtual void callbackNotInterpolatable_(IParameterObj* obj, ParameterBase* param,
                                            ResParameterObj res_obj1, ResParameterObj res_obj2,
                                            ResParameter res_param1, ResParameter res_param2,
                                            f32 t);

    void setParameterListName_(const sead::SafeString& name);
    void applyResParameterList_(bool, ResParameterList list1, ResParameterList list2, f32 t);
    ResParameterObj searchResParameterObj_(ResParameterList list, const IParameterObj& obj) const;
    void searchChildParameterObj_(ResParameterObj res_obj, IParameterObj* obj) const;
    void applyResParameterObjB_(bool, ResParameterList list, f32 t);
    void searchResParameterList_(ResParameterList res_list, const IParameterList& list) const;
    void searchChildParameterList_(ResParameterList res_list) const;
    void applyResParameterListB_(bool, ResParameterList res_list, f32 t);
};

}  // namespace agl::utl
