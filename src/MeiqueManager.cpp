#include "MeiqueManager.h"
#include "Constants.h"
#include "MeiqueProject.h"

MeiqueManager::MeiqueManager()
{
}

QString MeiqueManager::mimeType() const
{
    return MEIQUE_MIMETYPE;
}

ProjectExplorer::Project* MeiqueManager::openProject(const QString& fileName, QString* errorString)
{
    if (!QFileInfo(fileName).isFile()) {
        *errorString = tr("Failed opening project '%1': Project is not a file").arg(fileName);
        return nullptr;
    }

    try {
        return new MeiqueProject(this, fileName);
    } catch (const QString& msg) {
        *errorString = tr("Failed opening project '%1': %2").arg(fileName).arg(msg);
        return nullptr;
    }
}

#include "MeiqueManager.moc"
