#ifndef MeiqueProjectNode_h
#define MeiqueProjectNode_h

#include <projectexplorer/projectnodes.h>

namespace Meique {

class ProjectNode : public ProjectExplorer::ProjectNode
{
public:
    ProjectNode(const QString& projectFilePath)
        : ProjectExplorer::ProjectNode(projectFilePath)
    {
    }

    QList<ProjectExplorer::ProjectAction> supportedActions(Node*) const override { return QList<ProjectExplorer::ProjectAction>(); }

    bool canAddSubProject(const QString&) const override { return false; }

    bool addSubProjects(const QStringList&) override { return false; }

    bool removeSubProjects(const QStringList&) override { return false; }

    bool addFiles(const QStringList&, QStringList*) override { return false; }
    bool removeFiles(const QStringList&, QStringList*) override { return false; }
    bool deleteFiles(const QStringList&) override { return false; }
    bool renameFile(const QString&, const QString&) override { return false; }
};

}

#endif
