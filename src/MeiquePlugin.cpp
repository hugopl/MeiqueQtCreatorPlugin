#include "MeiquePlugin.h"
#include "MeiqueProjectManager.h"

#include <coreplugin/icore.h>
#include <coreplugin/mimedatabase.h>
#include <QtPlugin>

namespace Meique {

bool Plugin::initialize(const QStringList&, QString* errorString)
{
    if (!Core::MimeDatabase::addMimeTypes(QLatin1String(":meiqueproject/MeiqueProject.mimetypes.xml"), errorString))
        return false;

    ProjectManager* manager = new ProjectManager;
    addAutoReleasedObject(manager);
    return true;
}

void Plugin::extensionsInitialized()
{
}

}

Q_EXPORT_PLUGIN(Meique::Plugin)

#include "MeiquePlugin.moc"
