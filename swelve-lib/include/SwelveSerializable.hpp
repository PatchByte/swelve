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

    class SwelveString : public SwelveSerializable
    {
    public:
        static constexpr size_t smStringLimitations = 0x200;

        SwelveString(std::string content): str(content) {};
        SwelveString(const char* content): str(content) {};
        SwelveString(): str("") {}

        size_t GetSerializableSize();
        void Export(SwelveStream& stream);
        void Import(SwelveStream& stream);

        std::string str;
    };

}