#ifndef MeiqueProject_h
#define MeiqueProject_h

#include <QFileSystemWatcher>
#include <QFuture>
#include <projectexplorer/project.h>

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

    virtual QString displayName() const override;
    virtual Core::IDocument* document() const override;
    virtual ProjectExplorer::IProjectManager* projectManager() const override;
    virtual ProjectExplorer::ProjectNode* rootProjectNode() const override;

    virtual QStringList files(FilesMode fileMode) const override;
private slots:
    void projectFileChanged(const QString&);
private:
    ProjectManager* m_manager;
    QString m_fileName;
    QString m_projectName;
    ProjectNode* m_rootNode;
    MeiqueDocument* m_document;

    QString m_buildDir;
    QStringList m_fileList;

    QFuture<void> m_codeModelFuture;
    QFileSystemWatcher* m_watcher;

    void parseProject();
};

}

#endif
