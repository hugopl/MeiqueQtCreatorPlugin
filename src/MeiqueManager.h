#ifndef MeiqueManager_h
#define MeiqueManager_h

#include <projectexplorer/iprojectmanager.h>

class MeiqueManager : public ProjectExplorer::IProjectManager
{
    Q_OBJECT

public:
    MeiqueManager();

    virtual QString mimeType() const;
    virtual ProjectExplorer::Project* openProject(const QString& fileName, QString* errorString);
};

#endif
