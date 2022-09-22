#pragma once

#include "SwelveDeclarations.hpp"
#include "SwelveUtils.hpp"

#include <vector>
#include <map>

namespace swelve
{
    class SwelveManifest
    {
    public:
        SwelveManifest();
        virtual ~SwelveManifest();

        std::map<SwelveHash, SwelveExtension*> entries;
    };
}