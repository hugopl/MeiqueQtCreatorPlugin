#ifndef MeiqueProject_h
#define MeiqueProject_h

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

    virtual QString displayName() const;
    virtual Core::Id id() const;
    virtual Core::IDocument* document() const;
    virtual ProjectExplorer::IProjectManager* projectManager() const;
    virtual ProjectExplorer::ProjectNode* rootProjectNode() const;

    virtual QStringList files(FilesMode fileMode) const;
private:
    MeiqueManager* m_manager;
    QString m_fileName;
    QString m_projectName;
    MeiqueProjectNode* m_rootNode;
    MeiqueDocument* m_document;

    QString m_buildDir;
    QStringList m_fileList;

    void parseProject();
};

#endif
