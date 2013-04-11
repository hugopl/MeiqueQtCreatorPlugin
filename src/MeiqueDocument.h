#ifndef MeiqueDocument_h
#define MeiqueDocument_h

#include <coreplugin/idocument.h>

class MeiqueDocument : public Core::IDocument
{
public:
    MeiqueDocument(const QString& fileName);

    virtual bool save(QString *errorString, const QString &fileName = QString(), bool autoSave = false);
    virtual QString fileName() const;
    virtual QString defaultPath() const;
    virtual QString suggestedFileName() const;
    virtual QString mimeType() const;

    virtual bool isModified() const;
    virtual bool isSaveAsAllowed() const;

    virtual ReloadBehavior reloadBehavior(ChangeTrigger state, ChangeType type) const;
    virtual bool reload(QString *errorString, ReloadFlag flag, ChangeType type);
    virtual void rename(const QString &newName);

private:
    QString m_fileName;
};

#endif
