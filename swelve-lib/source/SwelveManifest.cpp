#include "SwelveManifest.hpp"

namespace swelve
{

    SwelveManifestEntry::SwelveManifestEntry():
        linkedIdentifier(-1),
        linkedExtension(nullptr),
        linkedHasBeenResolved(false)
    {
    }

    SwelveManifest::SwelveManifest():
        entries(new std::vector<SwelveManifestEntry*>())
    {}

    SwelveManifest::~SwelveManifest()
    {
        if(entries)
        {
            delete entries;
            entries = nullptr;
        }
    }

}