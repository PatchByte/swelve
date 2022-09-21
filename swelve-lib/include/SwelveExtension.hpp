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
    public:
        bool allowDeallocationOfName;
        bool allowDeallocationOfDesc;

        const char* name;
        const char* description;
    };

    class SwelveReader
    {
    public:
        virtual SwelveExtension* ReadExtension(SwelveStream& extensionStream);
    };

    class SwelveWriter
    {
    public:
        virtual size_t GetExtensionWriteSize(SwelveExtension* input);

        virtual bool WriteExtension(SwelveExtension* input, SwelveStream& extensionStream);
    };

}