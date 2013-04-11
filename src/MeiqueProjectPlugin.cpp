#include "MeiqueProjectPlugin.h"
#include "MeiqueManager.h"

#include <coreplugin/icore.h>
#include <coreplugin/mimedatabase.h>
#include <QtPlugin>

MeiqueProjectPlugin::MeiqueProjectPlugin()
{
}

bool MeiqueProjectPlugin::initialize(const QStringList& arguments, QString* errorString)
{
    if (!Core::ICore::mimeDatabase()->addMimeTypes(QLatin1String(":meiqueproject/MeiqueProject.mimetypes.xml"), errorString))
        return false;

    MeiqueManager* manager = new MeiqueManager;
    addAutoReleasedObject(manager);
    return true;
}

void MeiqueProjectPlugin::extensionsInitialized()
{
}

Q_EXPORT_PLUGIN(MeiqueProjectPlugin)

#include "MeiqueProjectPlugin.moc"
