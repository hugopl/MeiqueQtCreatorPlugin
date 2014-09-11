qtCreatorLibPath = option("QtCreatorLibDir", "Where QtCreator plugins folder is.", "/usr/lib/qtcreator")

qtCore = findPackage("Qt5Core")
qtGui = findPackage("Qt5Gui")
qtWidgets = findPackage("Qt5Widgets")
qtNetwork = findPackage("Qt5Network")

configureFile("MeiqueProjectManager.pluginspec.in", "MeiqueProjectManager.pluginspec")

plugin = Library:new("MeiqueProjectManager")
-- QtCreator include paths
-- QtCreator include paths
plugin:addIncludePath(QTC_DIR.."/src/plugins")
plugin:addIncludePath(QTC_DIR.."/src/libs")
plugin:addIncludePath(QTC_DIR.."/src/libs/cplusplus")
plugin:addIncludePath(QTC_DIR.."/src/libs/3rdparty")
plugin:addIncludePath(QTC_DIR.."/src/libs/3rdparty/cplusplus")

plugin:addLibraryPath(qtCreatorLibPath)
plugin:addLibraryPath(qtCreatorLibPath.."/plugins")
plugin:addLibraryPath(qtCreatorLibPath.."/plugins/QtProject")

plugin:addLinkLibraries([[
Utils
ProjectExplorer
QtSupport
CppTools
]])

-- Qt modules
plugin:use(qtCore)
plugin:use(qtGui)
plugin:use(qtWidgets)
plugin:use(qtNetwork)
plugin:useQtAutomoc()
plugin:addQtResource("meiqueproject.qrc")

plugin:addFiles([[
MeiquePlugin.cpp
MeiqueProjectManager.cpp
MeiqueProject.cpp
]])

