qtcSrc = option("QtCreatorSources", "Where the QtCreator sources are located")
abortIf(not qtcSrc, "You need the QtCreator sources to compile QtCreator plugins")

-- Identify QtCreator version
-- This also proves that meique needs a way to store variables in meiquecache.lua
-- so this "grep" can be cached.
f = io.open(qtcSrc.value.."/qtcreator.pri", "r")
abortIf(f == nil, qtcSrc.value.."/qtcreator.pri not found!")
s = f:read("*all")
f:close()
_, _, QTCREATOR_VERSION = string.find(s, "QTCREATOR_VERSION = (3.0.%d)")

QT_VERSION = "4.8"
qtCore = findPackage("QtCore", QT_VERSION, REQUIRED)
qtGui = findPackage("QtGui", QT_VERSION, REQUIRED)
qtNetwork = findPackage("QtNetwork", QT_VERSION, REQUIRED)

configureFile("MeiqueProjectManager.pluginspec.in", "MeiqueProjectManager.pluginspec")

plugin = Library:new("MeiqueProjectManager")
-- QtCreator include paths
plugin:addIncludePath(qtcSrc.value.."/src/plugins")
plugin:addIncludePath(qtcSrc.value.."/src/libs")
plugin:addIncludePath(qtcSrc.value.."/src/libs/cplusplus")
plugin:addIncludePath(qtcSrc.value.."/src/libs/3rdparty")
plugin:addIncludePath(qtcSrc.value.."/src/libs/3rdparty/cplusplus")

-- Hardcoded QtCreator libraries path
plugin:addLibraryPaths([[
/usr/lib/qtcreator
/usr/lib/qtcreator/plugins
/usr/lib/qtcreator/plugins/QtProject
]])

plugin:addLinkLibraries([[
Utils
ProjectExplorer
QtSupport
CppTools
]])

-- Qt modules
plugin:use(qtCore)
plugin:use(qtGui)
plugin:use(qtNetwork)
plugin:useQtAutomoc()
plugin:addQtResource("meiqueproject.qrc")

plugin:addFiles([[
MeiqueProjectPlugin.cpp
MeiqueManager.cpp
MeiqueProject.cpp
MeiqueProjectNode.cpp
MeiqueDocument.cpp
]])

