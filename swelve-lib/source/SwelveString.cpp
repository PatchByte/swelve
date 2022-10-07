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

    void SwelveString::Export(SwelveStream& stream)
    {
        if(str.length() > smStringLimitations)
        {
            stream.Error();
            return;
        }

        stream.Write(str.length());
        stream.WriteRawBuffer((void*)str.c_str(), str.length());

    }

    void SwelveString::Import(SwelveStream& stream)
    {
        char* content = nullptr;
        size_t contentSize = 0;

        stream.Read(&contentSize);

        if(contentSize > smStringLimitations)
        {
            stream.Error();
            return;
        }
        
        content = new char[contentSize + 1];
        memset(content, 0, contentSize + 1);

        stream.ReadRawBuffer(content, contentSize);

        str.append(content);

        delete[] content;
    }

}