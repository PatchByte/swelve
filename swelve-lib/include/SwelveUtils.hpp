#pragma once

namespace swelve
{

    // Please don't judge me about the code.

    class SwelveStream
    {
    private:
        void* dataBuffer;
        unsigned long long dataCursor;
        unsigned long long dataLength;
    public:
        SwelveStream(void* data, unsigned long long dataLength):
            dataBuffer(data),
            dataLength(dataLength),
            dataCursor(0)
        {}

        unsigned long long GetCursor() { return dataCursor; }

        unsigned long long GetSizeOfData() { return dataLength; }

        void SetCursor(unsigned long long pos) { dataCursor = pos; }

        void AddCursor(unsigned long long pos) { dataCursor += pos; }

        void SubCursor(unsigned long long pos) { dataCursor -= pos; }

        bool IsEOF() { return dataCursor >= dataLength; }

        template<typename T>
        T* Read(T* buffer)
        {
            if(IsEOF())
            {
                return nullptr;
            }

            for(unsigned long long i = 0; i < sizeof(T); i++)
            {
                static_cast<uint8_t*>(buffer)[i] = static_cast<uint8_t*>(dataBuffer)[dataCursor+i];
            }

            dataCursor += sizeof(T);

            return buffer;
        }

        template<typename T>
        T* Write(T* buffer)
        {
            if(IsEOF())
            {
                return nullptr;
            }

            for(unsigned long long i = 0; i < sizeof(T); i++)
            {
                static_cast<uint8_t*>(dataBuffer)[dataCursor+i] = static_cast<uint8_t*>(buffer)[i];
            }

            dataCursor += sizeof(T);

            return buffer;
        }

        void* ReadRawBuffer(void* buffer, unsigned long long len)
        {
            if(IsEOF())
            {
                return nullptr;
            }

            for(unsigned long long i = 0; i < len; i++)
            {
                static_cast<uint8_t*>(buffer)[i] = static_cast<uint8_t*>(dataBuffer)[dataCursor+i];
            }

            dataCursor += len;

            return buffer;
        }

        void* WriteRawBuffer(void* buffer, unsigned long long len)
        {
            if(IsEOF())
            {
                return nullptr;
            }

            for(unsigned long long i = 0; i < len; i++)
            {
                static_cast<uint8_t*>(dataBuffer)[dataCursor+i] = static_cast<uint8_t*>(buffer)[i];
            }

            dataCursor += len;

            return buffer;
        }
    };

}