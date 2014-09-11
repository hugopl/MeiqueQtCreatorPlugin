#ifndef MeiqueDocument_h
#define MeiqueDocument_h

#include <coreplugin/idocument.h>
#include "MeiqueConstants.h"

namespace Meique {

class MeiqueDocument : public Core::IDocument
{
public:
    MeiqueDocument()
    {
        setMimeType(Constants::MimeType);
    }
    bool save(QString*, const QString&, bool) override { return false; }
    QString defaultPath() const override { return QString(); }
    QString suggestedFileName() const override { return QString(); }

    bool isModified() const override { return false; }
    bool isSaveAsAllowed() const override { return false; }

    ReloadBehavior reloadBehavior(ChangeTrigger, ChangeType) const override { return BehaviorSilent; }
    bool reload(QString*, ReloadFlag, ChangeType) override { return false; }
};

}

#endif
