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
    if (!QFileInfo(fileName).isFile())
        return 0;

    return new MeiqueProject(this, fileName);
}

#include "MeiqueManager.moc"
