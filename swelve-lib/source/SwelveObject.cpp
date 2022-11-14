#include "SwelveObject.hpp"
#include "SwelveSerializable.hpp"
#include "SwelveUtils.hpp"

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

    SwelveObject::SwelveObject(SwelveStream importBufferFrom)
    {
        objectSize = importBufferFrom.GetSizeOfData();
        objectBuffer = new unsigned char[ objectSize ];

        if(objectBuffer)
        {
            memcpy(objectBuffer, importBufferFrom.GetDataBuffer(), objectSize);
        }
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