#pragma once

#include "agl/Utils/aglParameterList.h"

namespace sead {
class XmlDocument;
}

namespace agl::utl {

class IParameterIO : public IParameterList {
public:
    IParameterIO();
    IParameterIO(const sead::SafeString& name, u32);
    ~IParameterIO() override;

    virtual bool save(const sead::SafeString& path, u32) const;
    virtual void applyResParameterArchive(ResParameterArchive archive);
    virtual void applyResParameterArchiveLerp(ResParameterArchive archive1,
                                              ResParameterArchive archive2, f32 t);

    void load(const sead::SafeString& path, bool);
    void loadText(const void* data, u32 size, bool);

    bool isCompleteArchive(ResParameterArchive archive, bool) const;

    void genMessageIO(sead::hostio::Context* context, u32);
    void listenPropertyEventIO(sead::hostio::Reflexible* reflexible,
                               sead::hostio::PropertyEvent* event);

protected:
    virtual void callbackInvalidVersion_(ResParameterArchive archive);

    virtual void writeHeader_(sead::XmlElement* element, sead::Heap* heap) const;
    void save_(const sead::SafeString& path, const sead::XmlDocument* document) const;
};

}  // namespace agl::utl
