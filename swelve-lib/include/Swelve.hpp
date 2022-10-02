#pragma once

#include "SwelveDeclarations.hpp"
#include "SwelveUtils.hpp"

#include <Windows.h>
#include <iostream>
#include <functional>
#include <vector>
#include <map>
#include <stack>

#define SWELVE_IMPLEMENT_IO()   size_t GetSerializableSize(); \
                                void Export(swelve::SwelveStream& stream); \
                                void Import(swelve::SwelveStream& stream);

namespace swelve
{

    class SwelveInstance
    {
    public:
        SwelveInstance();
        virtual ~SwelveInstance();

        virtual SwelveReader* CreateReader();
        virtual SwelveWriter* CreateWriter();

        virtual SwelveManifest* ParseManifest(SwelveStream& extensionStream);
        virtual SwelveExtension* ParseExtension(SwelveStream& extensionStream);

        virtual void PushResolveCallback(SwelveManifestResolveCallback* callback);
        virtual void PopResolveCallback();

    public:
        std::vector<SwelveManifest*> swelveManifestList;
        std::map<SwelveHash, SwelveExtension*> swelveExtensionMap;
        std::stack<SwelveManifestResolveCallback*> resolveCallbackStack;

        SwelveManifestResolveCallback* swelveResolveCallback;
    };

}