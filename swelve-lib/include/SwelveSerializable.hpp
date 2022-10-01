#pragma once

#include "SwelveDeclarations.hpp"
#include "SwelveUtils.hpp"

namespace swelve
{

    class SwelveSerializable
    {
    public:
        virtual size_t GetSerializableSize() = 0;
        virtual void Export(SwelveStream& stream) = 0;
        virtual void Import(SwelveStream& stream) = 0;
    };

}