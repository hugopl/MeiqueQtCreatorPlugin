#ifndef MeiqueProjectNode_h
#define MeiqueProjectNode_h

#include <projectexplorer/projectnodes.h>

class MeiqueProjectNode : public ProjectExplorer::ProjectNode
{
    friend class MeiqueProject;
public:
    MeiqueProjectNode(const QString& projectFilePath);

    virtual bool hasBuildTargets() const override;

    virtual QList<ProjectAction> supportedActions(Node* node) const override;

    virtual bool canAddSubProject(const QString& proFilePath) const override;

    virtual bool addSubProjects(const QStringList& proFilePaths) override;

    virtual bool removeSubProjects(const QStringList& proFilePaths) override;

    virtual bool addFiles(const QStringList& filePaths, QStringList* notAdded = 0) override;
    virtual bool removeFiles(const QStringList& filePaths, QStringList* notRemoved = 0) override;
    virtual bool deleteFiles(const QStringList& filePaths) override;
    virtual bool renameFile(const QString& filePath, const QString& newFilePath) override;

    virtual QList<ProjectExplorer::RunConfiguration *> runConfigurationsFor(Node*) override;
};

#endif
