#pragma once

#ifndef _WIN32
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <cstring>
#else
#include <Windows.h>
#endif
#include <format>
#include <sstream>
#include <fstream>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <swelve-lib/include/Swelve.hpp>
#include <swelve-lib/include/SwelveObject.hpp>
#include <swelve-lib/include/SwelveUtils.hpp>
#include <swelve-lib/include/SwelveExtension.hpp>
#include <swelve-lib/include/SwelveManifest.hpp>
#include <swelve-lib/include/SwelveSerializable.hpp>
namespace test
{

    void ReadWriteExtensions();
    void ReadWriteManifest();
    void ReadWriteString();

}