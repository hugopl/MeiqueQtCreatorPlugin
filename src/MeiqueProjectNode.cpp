#include "MeiqueProjectNode.h"

MeiqueProjectNode::MeiqueProjectNode(const QString& projectFilePath)
    : ProjectExplorer::ProjectNode(projectFilePath)
{
}

bool MeiqueProjectNode::hasBuildTargets() const
{
    return false;
}

QList<ProjectExplorer::ProjectNode::ProjectAction> MeiqueProjectNode::supportedActions(Node* node) const
{
    return QList<ProjectExplorer::ProjectNode::ProjectAction>();
}

bool MeiqueProjectNode::canAddSubProject(const QString& proFilePath) const
{
    return false;
}

bool MeiqueProjectNode::addSubProjects(const QStringList& proFilePaths)
{
    return false;
}

bool MeiqueProjectNode::removeSubProjects(const QStringList& proFilePaths)
{
    return false;
}

bool MeiqueProjectNode::addFiles(const QStringList& filePaths, QStringList* notAdded)
{
    return false;
}

bool MeiqueProjectNode::removeFiles(const QStringList& filePaths, QStringList* notRemoved)
{
    return false;
}

bool MeiqueProjectNode::deleteFiles(const QStringList& filePaths)
{
    return false;
}

bool MeiqueProjectNode::renameFile(const QString& filePath, const QString& newFilePath)
{
    return false;
}

QList<ProjectExplorer::RunConfiguration*> MeiqueProjectNode::runConfigurationsFor(Node*)
{
    return QList<ProjectExplorer::RunConfiguration*>();
}
