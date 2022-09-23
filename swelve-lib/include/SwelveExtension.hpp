#pragma once

#include "SwelveDeclarations.hpp"
#include "SwelveUtils.hpp"

namespace swelve
{
    enum SwelveExtensionBaseFlags_ : SwelveHash
    {
        SwelveExtensionBaseFlags_BaseExtension = 1 << 0,
    };

    class SwelveExtension
    {
    public:
        SwelveExtension();
        virtual ~SwelveExtension();

        virtual const char* GetName();
        virtual const char* GetDescription();

        virtual void* GetAdditionalInformations();
        virtual SwelveHash GetAdditionalFlags();

        virtual SwelveHash GetIdentifier();
        
        virtual void OnLoad() {};
        virtual void OnUnload() {};
    public:
        bool allowDeallocationOfName;
        bool allowDeallocationOfDesc;

        const char* name;
        const char* description;

        SwelveHash identifier;
    };
    
    class SwelveReader
    {
    public:
        virtual SwelveExtension* ReadExtension(SwelveStream& extensionStream);
        virtual SwelveManifest* ReadManfiest(SwelveStream& extensionStream, SwelveManifestResolveCallback* resolveCallback);
    };

    class SwelveWriter
    {
    public:
        virtual size_t GetExtensionWriteSize(SwelveExtension* input);
        virtual size_t GetManifestWriteSize(SwelveManifest* input);

        virtual bool WriteExtension(SwelveExtension* input, SwelveStream& extensionStream);
        virtual bool WriteManifest(SwelveManifest* input, SwelveStream& manifestStream);
    };

}