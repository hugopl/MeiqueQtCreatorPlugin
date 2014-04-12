#ifndef MeiqueProjectPlugin_h
#define MeiqueProjectPlugin_h

#include <extensionsystem/iplugin.h>

namespace Meique {

class Plugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin")

public:
    Plugin() { }

    bool initialize(const QStringList& arguments, QString* errorString) override;
    void extensionsInitialized() override;
};

}

#endif

