#include "MeiqueProject.h"
#include "MeiqueConstants.h"
#include "MeiqueDocument.h"
#include "MeiqueProjectNode.h"
#include "MeiqueProjectManager.h"

#include <coreplugin/icontext.h>
#include <cpptools/cppmodelmanagerinterface.h>
#include <projectexplorer/projectexplorerconstants.h>
#include <QMap>
#include <QProcess>
#include <QDebug>

#include <projectexplorer/headerpath.h>
#include <projectexplorer/kitinformation.h>
#include <projectexplorer/kitmanager.h>
#include <projectexplorer/toolchain.h>
#include <projectexplorer/target.h>

namespace Meique {

Project::Project(ProjectManager* manager, const QString& fileName)
    : m_manager(manager)
    , m_fileName(fileName)
    , m_rootNode(new ProjectNode(fileName))
    , m_document(new MeiqueDocument)
    , m_watcher(new QFileSystemWatcher(this))
{
    setId(Constants::ProjectId);
    setProjectContext(Core::Context(Constants::ProjectContext));
    setProjectLanguages(Core::Context(ProjectExplorer::Constants::LANG_CXX));

    QDir buildDir = QFileInfo(fileName).dir();
    // TODO make build dir configurable.
    if (!buildDir.cd("build")) {
        buildDir.mkdir("build");
        // TODO alert when this fail.
        buildDir.cd("build");
    }
    m_buildDir = buildDir.canonicalPath();

    connect(m_watcher, SIGNAL(fileChanged(QString)), this, SLOT(projectFileChanged(QString)));

    parseProject();
}

Project::~Project()
{
    m_codeModelFuture.cancel();
    delete m_rootNode;
}

QString Project::displayName() const
{
    return m_projectName;
}

Core::IDocument* Project::document() const
{
    return m_document;
}

ProjectExplorer::IProjectManager* Project::projectManager() const
{
    return m_manager;
}

ProjectExplorer::ProjectNode* Project::rootProjectNode() const
{
    return m_rootNode;
}

QStringList Project::files(FilesMode fileMode) const
{
    return m_fileList;
}

void Project::projectFileChanged(const QString&)
{
    parseProject();
}

void Project::parseProject()
{
    m_fileList.clear();
    QStringList includeDirs;

    foreach (const QString& file, m_watcher->files())
        m_watcher->removePath(file);

    QProcess proc;
    proc.setWorkingDirectory(m_buildDir);
    // TODO: replace by meique found by the configuration
    proc.start("meique", QStringList() << "-d" << "--meique-dump-project");
    proc.waitForStarted();
    proc.closeWriteChannel();
    proc.waitForFinished();
    QList<QByteArray> output = proc.readAllStandardOutput().split('\n');
    QByteArray error = proc.readAllStandardError();
    if (!error.isEmpty())
        throw QString::fromUtf8(error);

    typedef QMap<ProjectExplorer::FolderNode*, QList<ProjectExplorer::FileNode*> > NodeTree;
    typedef QMapIterator<ProjectExplorer::FolderNode*, QList<ProjectExplorer::FileNode*> > NodeTreeIterator;

    NodeTree tree;
    ProjectExplorer::FolderNode* currentParentNode = m_rootNode;

    foreach (QByteArray file, output) {
        if (file.startsWith("File:")) {
            QString filePath = file.mid(sizeof("File:"));
            tree[currentParentNode] << new ProjectExplorer::FileNode(filePath, ProjectExplorer::SourceType, false);
            m_fileList << filePath;
        } else if (file.startsWith("Target: ")) {
            currentParentNode = new ProjectExplorer::FolderNode(file.mid(sizeof("Target:")));
            tree[currentParentNode];
        } else if (file.startsWith("Include: ")) {
             includeDirs << file.mid(sizeof("Include:"));
        } else if (file.startsWith("ProjectFile:")) {
            QString filePath = file.mid(sizeof("ProjectFile:"));
            m_watcher->addPath(filePath);
            m_fileList << filePath;
        } else if (file.startsWith("Project: ")) {
            m_projectName = file.mid(sizeof("Project:"));
            emit displayNameChanged();
        }
    }

    // The lazy and stupid way...
    m_rootNode->removeFolderNodes(m_rootNode->subFolderNodes());

    m_rootNode->addFolderNodes(tree.keys());
    NodeTreeIterator i(tree);
    while (i.hasNext()) {
        i.next();
        i.key()->addFileNodes(i.value());
    }

    CppTools::CppModelManagerInterface* modelManager = CppTools::CppModelManagerInterface::instance();
    CppTools::CppModelManagerInterface::ProjectInfo pinfo = modelManager->projectInfo(this);

    pinfo.clearProjectParts();
    CppTools::ProjectPart::Ptr part(new CppTools::ProjectPart);
    part->project = this;
    part->displayName = displayName();
    part->projectFile = projectFilePath();
    part->includePaths << includeDirs;

    CppTools::ProjectFileAdder adder(part->files);
    foreach (const QString& file, m_fileList)
        adder.maybeAdd(file);

    ProjectExplorer::Kit* k = activeTarget() ? activeTarget()->kit() : ProjectExplorer::KitManager::defaultKit();
    QStringList cxxflags("-std=c++0x");

    ProjectExplorer::ToolChain* tc = ProjectExplorer::ToolChainKitInformation::toolChain(k);
    part->evaluateToolchain(tc, cxxflags, cxxflags, ProjectExplorer::SysRootKitInformation::sysRoot(k));

    pinfo.appendProjectPart(part);
    m_codeModelFuture.cancel();
    m_codeModelFuture = modelManager->updateProjectInfo(pinfo);

    setProjectLanguage(ProjectExplorer::Constants::LANG_CXX, !part->files.isEmpty());

    emit fileListChanged();
}

}

#include "MeiqueProject.moc"
