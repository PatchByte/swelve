#include "Swelve.hpp"
#include "SwelveExtension.hpp"
#include "SwelveManifest.hpp"

namespace swelve
{
    SwelveInstance::SwelveInstance():
        swelveManifestList(),
        swelveExtensionMap(),
        swelveResolveCallback
        ([] (SwelveHash) -> SwelveExtension* { return nullptr; })
    {
    }

    SwelveInstance::~SwelveInstance()
    {
    }

    SwelveReader* SwelveInstance::CreateReader()
    {
        return new SwelveReader();
    }

    SwelveWriter* SwelveInstance::CreateWriter()
    {
        return new SwelveWriter();
    }

    SwelveManifest* SwelveInstance::ParseManifest(SwelveStream& extensionStream)
    {
        SwelveReader* reader = this->CreateReader();
        SwelveManifest* manifest = reader->ReadManfiest(extensionStream, this->swelveResolveCallback);

        for(auto currentManifestEntry : manifest->entries)
        {
            SwelveExtension* ext = currentManifestEntry.second;
            swelveExtensionMap[ext->GetIdentifier()] = ext;
        }

        this->swelveManifestList.push_back(manifest);

        delete reader;

        return manifest;
    }

    SwelveExtension* SwelveInstance::ParseExtension(SwelveStream& extensionStream)
    {
        SwelveReader* reader = this->CreateReader();
        SwelveExtension* ext = reader->ReadExtension(extensionStream);

        swelveExtensionMap[ext->GetIdentifier()] = ext;

        delete reader;

        return ext;
    }

    // Callback Stack

    void SwelveInstance::PushResolveCallback(SwelveManifestResolveCallback* callback)
    {
        swelveResolveCallback = callback;
        resolveCallbackStack.push(callback);
    }

    void SwelveInstance::PopResolveCallback()
    {
        swelveResolveCallback = resolveCallbackStack.top();
        resolveCallbackStack.pop();
    }
}