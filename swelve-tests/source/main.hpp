#pragma once

#include <Windows.h>
#include <format>
#include <sstream>
#include <fstream>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

namespace test
{

    void ReadWriteExtensions();
    void ReadWriteManifest();

}