#include "SwelveSerializable.hpp"

#include <cstring>
#include <cstdint>

static_assert(sizeof(size_t) == 0x08);

namespace swelve
{

    size_t SwelveString::GetSerializableSize()
    {
        return sizeof(size_t) + str.length();
    }

    bool SwelveString::Export(SwelveStream& stream)
    {
        if(str.length() > smStringLimitations)
        {
            return false;
        }

        stream.Write(str.length());
        stream.WriteRawBuffer((void*)str.c_str(), str.length());

        return true;
    }

    bool SwelveString::Import(SwelveStream& stream)
    {
        char* content = nullptr;
        size_t contentSize = 0;

        stream.Read(&contentSize);

        if(contentSize > smStringLimitations)
        {
            return false;
        }
        
        content = new char[contentSize + 1];
        memset(content, 0, contentSize + 1);

        stream.ReadRawBuffer(content, contentSize);

        str.append(content);

        delete[] content;

        return true;
    }

}