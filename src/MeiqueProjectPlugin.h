#ifndef MeiqueProjectPlugin_h
#define MeiqueProjectPlugin_h

#include <extensionsystem/iplugin.h>

class MeiqueProjectPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "MeiqueProjectManager.json")

public:

    MeiqueProjectPlugin();

    virtual bool initialize(const QStringList& arguments, QString* errorString);
    virtual void extensionsInitialized();
};

#endif
