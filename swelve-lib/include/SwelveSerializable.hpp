#pragma once

#include "SwelveDeclarations.hpp"
#include "SwelveUtils.hpp"

#include <string>

namespace swelve
{

    class SwelveSerializable
    {
    public:
        virtual size_t GetSerializableSize() = 0;
        virtual void Export(SwelveStream& stream) = 0;
        virtual void Import(SwelveStream& stream) = 0;
    };

    class SwelveString
    {
    public:
        static constexpr size_t smStringLimitations = 0x200;

        SwelveString(std::string content);
        SwelveString(const char* content);
        SwelveString(SwelveStream& stream);

        virtual ~SwelveString();

        virtual size_t GetSerializableSize();
        virtual bool Export(SwelveStream& stream);
        virtual bool Import(SwelveStream& stream);

        std::string str;
    };

}