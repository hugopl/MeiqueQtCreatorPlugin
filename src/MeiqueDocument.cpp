#include "MeiqueDocument.h"
#include "Constants.h"

MeiqueDocument::MeiqueDocument(const QString& fileName)
    : m_fileName(fileName)
{
}

bool MeiqueDocument::save(QString *errorString, const QString &fileName, bool autoSave)
{
    return false;
}

QString MeiqueDocument::fileName() const
{
    return m_fileName;
}

QString MeiqueDocument::defaultPath() const
{
    return QString();
}

QString MeiqueDocument::suggestedFileName() const
{
    return QString();
}

QString MeiqueDocument::mimeType() const
{
    return MEIQUE_MIMETYPE;
}

bool MeiqueDocument::isModified() const
{
    return false;
}

bool MeiqueDocument::isSaveAsAllowed() const
{
    return false;
}

Core::IDocument::ReloadBehavior MeiqueDocument::reloadBehavior(ChangeTrigger state, ChangeType type) const
{
    return BehaviorSilent;
}

bool MeiqueDocument::reload(QString *errorString, ReloadFlag flag, ChangeType type)
{
    return false;
}

void MeiqueDocument::rename(const QString &newName)
{
}
