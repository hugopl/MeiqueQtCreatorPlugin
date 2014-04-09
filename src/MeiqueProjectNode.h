#ifndef MeiqueProjectNode_h
#define MeiqueProjectNode_h

#include <projectexplorer/projectnodes.h>

class MeiqueProjectNode : public ProjectExplorer::ProjectNode
{
public:
    MeiqueProjectNode(const QString& projectFilePath)
        : ProjectExplorer::ProjectNode(projectFilePath)
    {
    }

    virtual bool canAddSubProject(const QString&) const override { return false; }

    virtual bool addSubProjects(const QStringList&) override { return false; }

    virtual bool removeSubProjects(const QStringList&) override { return false; }

    virtual bool addFiles(const QStringList&, QStringList*) override { return false; }
    virtual bool removeFiles(const QStringList&, QStringList*) override { return false; }
    virtual bool deleteFiles(const QStringList&) override { return false; }
    virtual bool renameFile(const QString&, const QString&) override { return false; }

    virtual QList<ProjectExplorer::RunConfiguration*> runConfigurationsFor(Node*) override { return QList<ProjectExplorer::RunConfiguration*>(); }
};

#endif
