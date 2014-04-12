#include "MeiqueProjectManager.h"
#include "MeiqueConstants.h"
#include "MeiqueProject.h"

namespace Meique {

ProjectManager::ProjectManager()
{
}

QString ProjectManager::mimeType() const
{
    return Constants::MimeType;
}

ProjectExplorer::Project* ProjectManager::openProject(const QString& fileName, QString* errorString)
{
    if (!QFileInfo(fileName).isFile()) {
        *errorString = tr("Failed opening project '%1': Project is not a file").arg(fileName);
        return nullptr;
    }

    try {
        return new Project(this, fileName);
    } catch (const QString& msg) {
        *errorString = tr("Failed opening project '%1': %2").arg(fileName).arg(msg);
        return nullptr;
    }
}

}

#include "MeiqueManager.moc"
