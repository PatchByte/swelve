#pragma once

#include "SwelveDeclarations.hpp"
#include "SwelveUtils.hpp"

namespace swelve
{

    class SwelveObject
    {
    public:
        SwelveObject(size_t objectSize);
        SwelveObject(SwelveSerializable* importFrom);
        SwelveObject(SwelveStream importBufferFrom);

        ~SwelveObject();

        SwelveStream Stream();
    private:
        void* objectBuffer;
        size_t objectSize;
    };

}