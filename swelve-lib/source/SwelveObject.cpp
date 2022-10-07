#include "SwelveObject.hpp"
#include "SwelveSerializable.hpp"

namespace swelve
{

    SwelveObject::SwelveObject(size_t _objectSize):
        objectSize(_objectSize)
    {
        objectBuffer = new unsigned char[objectSize];
    }

    SwelveObject::SwelveObject(SwelveSerializable* objectSerializable)
    {
        objectSize = objectSerializable->GetSerializableSize();
        objectBuffer = new unsigned char[objectSize];

        SwelveStream objectStream = SwelveObject::Stream();

        objectSerializable->Export(objectStream);
    }

    SwelveObject::~SwelveObject()
    {
        if(objectBuffer)
        {
            objectSize = 0;
            delete[] (unsigned char*)objectBuffer;
        }
    }

    SwelveStream SwelveObject::Stream()
    {
        return SwelveStream(objectBuffer, objectSize);
    }

}