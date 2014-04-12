#ifndef MeiqueManager_h
#define MeiqueManager_h

#include <projectexplorer/iprojectmanager.h>

namespace Meique {

class ProjectManager : public ProjectExplorer::IProjectManager
{
    Q_OBJECT

public:
    ProjectManager();

    virtual QString mimeType() const;
    virtual ProjectExplorer::Project* openProject(const QString& fileName, QString* errorString);
};

}

#endif
