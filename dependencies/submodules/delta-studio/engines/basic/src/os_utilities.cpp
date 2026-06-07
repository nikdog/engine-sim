#include "../include/os_utilities.h"

#include "../include/path.h"

#ifdef _MSC_VER
#include <Windows.h>
#else
#include <dlfcn.h>
#include <unistd.h>
#endif

dbasic::Path dbasic::GetModulePath() {
    char path[256];
#ifdef _MSC_VER
    DWORD result = GetModuleFileName(NULL, path, 256);
#else
    ssize_t count = readlink("/proc/self/exe", path, 256);
    if (count != -1) {
        path[count] = '\0';
    } else {
        path[0] = '\0';
    }
#endif

    Path fullPath = Path(path);
    Path parentPath;

    fullPath.GetParentPath(&parentPath);

    return parentPath;
}
