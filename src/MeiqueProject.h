#ifndef MeiqueProject_h
#define MeiqueProject_h

#include <QFileSystemWatcher>
#include <QFuture>
#include <projectexplorer/project.h>

class MeiqueManager;
class MeiqueProjectNode;
class MeiqueDocument;

class MeiqueProject : public ProjectExplorer::Project
{
    Q_OBJECT
public:
    MeiqueProject(MeiqueManager* manager, const QString& fileName);
    ~MeiqueProject();

    virtual QString displayName() const override;
    virtual Core::Id id() const override;
    virtual Core::IDocument* document() const override;
    virtual ProjectExplorer::IProjectManager* projectManager() const override;
    virtual ProjectExplorer::ProjectNode* rootProjectNode() const override;

    virtual QStringList files(FilesMode fileMode) const override;
private slots:
    void projectFileChanged(const QString&);
private:
    MeiqueManager* m_manager;
    QString m_fileName;
    QString m_projectName;
    MeiqueProjectNode* m_rootNode;
    MeiqueDocument* m_document;

    QString m_buildDir;
    QStringList m_fileList;

    QFuture<void> m_codeModelFuture;
    QFileSystemWatcher* m_watcher;

    void parseProject();
};

#endif
