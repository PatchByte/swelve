#pragma once

#include <swelve-lib/include/Swelve.hpp>
#include <swelve-lib/include/SwelveExtension.hpp>
#include <swelve-lib/include/SwelveManifest.hpp>

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