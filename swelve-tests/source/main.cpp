#include "main.hpp"

int main(int argc, char const *argv[])
{
    freopen( "memory_leak_log.txt", "w", stderr);

    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDERR);

    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDERR);

    test::ReadWriteExtensions();
    test::ReadWriteManifest();

    _CrtDumpMemoryLeaks();
    _CrtDbgBreak();

    return 0;
}
