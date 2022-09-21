#pragma once

#include "SwelveDeclarations.hpp"
#include "SwelveUtils.hpp"

#include <vector>

namespace swelve
{

    class SwelveManifestEntry
    {
    public:
        SwelveManifestEntry();
        virtual ~SwelveManifestEntry();

        SwelveHash linkedIdentifier;
        SwelveExtension* linkedExtension;
        bool linkedHasBeenResolved;
    };

    class SwelveManifest
    {
    public:
        SwelveManifest();
        virtual ~SwelveManifest();

        std::vector<SwelveManifestEntry*>* entries;
    };

}