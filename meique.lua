requiresMeique("1.0")
GCC:addCustomFlags("-std=c++0x")

qtCreatorLibPath = option("QtCreatorLibDir", "Where QtCreator plugins folder is.", "/usr/lib/qtcreator")

function readQtCVersion()
    local f = io.popen("qtcreator -version 2>&1", 'r')
    local s = f:read('*a')
    f:close()
    local version = string.match(s, "Qt Creator (%d.%d.%d+)")
    abortIf(not version, "qtcreator not in your system PATH or we failed to find the QtCreator version in the output of 'qtcreator -version'.")
    return version
end

function getQtCreatorSources()
    if os.execute("test -d "..QTC_DIR) == 0 then
        return true
    end

    print("Downloading QtCreator sources... (using wget)")
    url = string.format("http://download.qt-project.org/official_releases/qtcreator/%s/%s/qt-creator-opensource-src-%s.tar.gz", QTC_SHORT_VERSION, QTC_VERSION, QTC_VERSION)
    if os.execute("cd "..buildDir().." && wget -c "..url) == 0 then
        untar = string.format("tar -xf %sqt-creator-opensource-src-%s.tar.gz -C %s", buildDir(), QTC_VERSION, buildDir())
        print(untar)
        abortIf(os.execute(untar) ~= 0, "Failed to untar QtCreator sources.")
    end
end

QTC_VERSION = readQtCVersion()
QTC_SHORT_VERSION = string.match(QTC_VERSION, "(%d.%d).%d+")
QTC_DIR = string.format("%sqt-creator-opensource-src-%s", buildDir(), QTC_VERSION)

getQtCreatorSources()

addSubdirectory("src")
