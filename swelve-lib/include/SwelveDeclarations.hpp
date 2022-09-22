#pragma once

#include <iostream>

namespace swelve
{

    using SwelveHash = uint64_t;
    typedef class SwelveExtension*(SwelveManifestResolveCallback)(SwelveHash identifier);

    class SwelveExtension;
    class SwelveReader;
    class SwelveWriter;
    class SwelveManifestEntry;
    class SwelveManifest;
    
}