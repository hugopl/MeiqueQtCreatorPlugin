#ifndef MeiqueProjectNode_h
#define MeiqueProjectNode_h

#include <projectexplorer/projectnodes.h>

class MeiqueProjectNode : public ProjectExplorer::ProjectNode
{
    friend class MeiqueProject;
public:
    MeiqueProjectNode(const QString& projectFilePath);

    virtual bool hasBuildTargets() const;

    virtual QList<ProjectAction> supportedActions(Node* node) const;

    virtual bool canAddSubProject(const QString& proFilePath) const;

    virtual bool addSubProjects(const QStringList& proFilePaths);

    virtual bool removeSubProjects(const QStringList& proFilePaths);

    virtual bool addFiles(const ProjectExplorer::FileType fileType, const QStringList& filePaths, QStringList* notAdded = 0);
    virtual bool removeFiles(const ProjectExplorer::FileType fileType, const QStringList& filePaths, QStringList* notRemoved = 0);
    virtual bool deleteFiles(const ProjectExplorer::FileType fileType, const QStringList& filePaths);
    virtual bool renameFile(const ProjectExplorer::FileType fileType, const QString& filePath, const QString& newFilePath);

    virtual QList<ProjectExplorer::RunConfiguration *> runConfigurationsFor(Node*);
};

#endif
