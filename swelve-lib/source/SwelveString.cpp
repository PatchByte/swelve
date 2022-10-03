#include "SwelveSerializable.hpp"

#include <cstring>
#include <cstdint>

static_assert(sizeof(size_t) == 0x08);

namespace swelve
{

    size_t SwelveString::GetSerializableSize()
    {

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

        str.append(content);

        delete[] content;

        return true;
    }

}