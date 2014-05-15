#ifndef MeiqueProject_h
#define MeiqueProject_h

#include <QFileSystemWatcher>
#include <QFuture>
#include <projectexplorer/project.h>
#include <projectexplorer/projectnodes.h>

namespace Meique {

class ProjectManager;
class ProjectNode;
class MeiqueDocument;

class Project : public ProjectExplorer::Project
{
    Q_OBJECT
public:
    Project(ProjectManager* manager, const QString& fileName);
    ~Project();

    QString displayName() const override;
    Core::IDocument* document() const override;
    ProjectExplorer::IProjectManager* projectManager() const override;
    ProjectExplorer::ProjectNode* rootProjectNode() const override;

    QStringList files(FilesMode) const override;
private slots:
    void projectFileChanged();
private:
    ProjectManager* m_manager;
    QString m_fileName;
    QString m_projectName;
    ProjectNode* m_rootNode;
    MeiqueDocument* m_document;

    QString m_buildDir;
    QDir m_projectDir;
    QSet<QString> m_files;


    QFuture<void> m_codeModelFuture;
    QFileSystemWatcher m_watcher;

    void parseProject(QString* error = 0);
    void addNodes(const QSet<QString>& nodes);
    void removeNodes(const QSet<QString>& nodes);
    ProjectExplorer::FolderNode* findFolderFor(const QStringList& path);
};

}

#endif
