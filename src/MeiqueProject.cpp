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
{
    setId(Constants::ProjectId);
    setProjectContext(Core::Context(Constants::ProjectContext));
    setProjectLanguages(Core::Context(ProjectExplorer::Constants::LANG_CXX));

    m_document->setFilePath(fileName);
    m_projectDir = QFileInfo(fileName).dir();

    QDir buildDir(m_projectDir);
    // TODO make build dir configurable.
    if (!buildDir.cd("build")) {
        buildDir.mkdir("build");
        // TODO alert when this fail.
        buildDir.cd("build");
    }
    m_buildDir = buildDir.canonicalPath();

    connect(&m_watcher, &QFileSystemWatcher::fileChanged, this, &Project::projectFileChanged);

    QString error;
    parseProject(&error);
    if (!error.isNull())
        throw error;
    qDebug() << m_watcher.files();
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

QStringList Project::files(FilesMode) const
{
    return QStringList(m_files.toList());
}

void Project::projectFileChanged()
{
    parseProject();
}

void Project::parseProject(QString* error)
{
    QProcess proc;
    proc.setWorkingDirectory(m_buildDir);
    // TODO: replace by meique found by the configuration
    proc.start("meique", QStringList() << "-d" << "--meique-dump-project");
    proc.waitForStarted();
    proc.closeWriteChannel();
    proc.waitForFinished();
    QList<QByteArray> output = proc.readAllStandardOutput().split('\n');
    QByteArray errorOutput = proc.readAllStandardError();
    if (!errorOutput.isEmpty()) {
        if (error)
            *error = QString::fromUtf8(errorOutput);
        return;
    }

    QStringList includeDirs;
    QSet<QString> oldFiles(m_files);
    m_files.clear();

    foreach (QByteArray file, output) {
        if (file.startsWith("File:")) {
            QString filePath = file.mid(sizeof("File:"));
            m_files << filePath;
        } else if (file.startsWith("Include: ")) {
             includeDirs << file.mid(sizeof("Include:"));
        } else if (file.startsWith("ProjectFile:")) {
            QString filePath = file.mid(sizeof("ProjectFile:"));
            m_watcher.addPath(filePath);
            m_files << filePath;
        } else if (file.startsWith("Project: ")) {
            m_projectName = file.mid(sizeof("Project:"));
            emit displayNameChanged();
        }
    }
    removeNodes(oldFiles - m_files);
    addNodes(m_files - oldFiles);

    CppTools::CppModelManagerInterface* modelManager = CppTools::CppModelManagerInterface::instance();
    CppTools::CppModelManagerInterface::ProjectInfo pinfo = modelManager->projectInfo(this);

    pinfo.clearProjectParts();
    CppTools::ProjectPart::Ptr part(new CppTools::ProjectPart);
    part->project = this;
    part->displayName = displayName();
    part->projectFile = projectFilePath();
    part->includePaths << includeDirs;

    CppTools::ProjectFileAdder adder(part->files);
    foreach (const QString& file, m_files)
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

void Project::addNodes(const QSet<QString>& nodes)
{
    using namespace ProjectExplorer;

    const QLatin1Char sep('/');
    QStringList path;
    for (const QString& node : nodes) {
        path = m_projectDir.relativeFilePath(node).split(sep);
        path.pop_back();
        FolderNode* folder = findFolderFor(path);
        folder->addFileNodes(QList<FileNode*>() << new FileNode(node, SourceType, false));
    }
}

void Project::removeNodes(const QSet<QString>& nodes)
{
    using namespace ProjectExplorer;

    const QLatin1Char sep('/');
    QStringList path;

    for (const QString& node : nodes) {
        path = m_projectDir.relativeFilePath(node).split(sep);
        path.pop_back();
        FolderNode* folder = findFolderFor(path);

        for (FileNode* file : folder->fileNodes()) {
            if (file->path() == node) {
                folder->removeFileNodes(QList<FileNode*>() << file);
                break;
            }
        }
    }
}

ProjectExplorer::FolderNode* Project::findFolderFor(const QStringList& path)
{
    using namespace ProjectExplorer;
    FolderNode* folder = m_rootNode;

    for (const QString& part : path) {
        bool folderFound = false;
        for (FolderNode* subFolder : folder->subFolderNodes()) {
            if (subFolder->displayName() == part) {
                folder = subFolder;
                folderFound = true;
                break;
            }
        }
        if (!folderFound) {
            FolderNode* newFolder = new FolderNode(part);
            folder->addFolderNodes(QList<FolderNode*>() << newFolder);
            folder = newFolder;
        }
    }
    return folder;
}

}

#include "MeiqueProject.moc"
