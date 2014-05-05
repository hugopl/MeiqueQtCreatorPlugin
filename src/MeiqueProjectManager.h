#ifndef MeiqueManager_h
#define MeiqueManager_h

#include <projectexplorer/iprojectmanager.h>

namespace Meique {

class ProjectManager : public ProjectExplorer::IProjectManager
{
    Q_OBJECT

public:
    ProjectManager();

    QString mimeType() const override;
    ProjectExplorer::Project* openProject(const QString& fileName, QString* errorString) override;
};

}

#endif
