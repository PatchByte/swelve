#pragma once

namespace swelve
{

    // Please don't judge me about the code.

    class SwelveStream
    {
    private:
        uint8_t* dataBuffer;
        unsigned long long dataCursor;
        unsigned long long dataLength;
    public:
        SwelveStream(void* data, unsigned long long dataLength):
            dataBuffer(static_cast<uint8_t*>(data)),
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
        T* Read(T* _buffer)
        {
            uint8_t *buffer = (uint8_t*)_buffer; 

            if(IsEOF())
            {
                return nullptr;
            }

            for(unsigned long long i = 0; i < sizeof(T); i++)
            {
                buffer[i] = dataBuffer[dataCursor+i];
            }

            dataCursor += sizeof(T);

            return _buffer;
        }

        template<typename T>
        void Write(T buffer)
        {
            Write(&buffer);
        }

        template<typename T>
        T* Write(T* _buffer)
        {
            uint8_t *buffer = (uint8_t*)_buffer; 

            if(IsEOF())
            {
                return nullptr;
            }

            for(unsigned long long i = 0; i < sizeof(T); i++)
            {
                dataBuffer[dataCursor+i] = buffer[i];
            }

            dataCursor += sizeof(T);

            return _buffer;
        }

        void* ReadRawBuffer(void* _buffer, unsigned long long len)
        {
            uint8_t *buffer = (uint8_t*)_buffer; 

            if(IsEOF())
            {
                return nullptr;
            }

            for(unsigned long long i = 0; i < len; i++)
            {
                buffer[i] = dataBuffer[dataCursor+i];
            }

            dataCursor += len;

            return _buffer;
        }

        void* WriteRawBuffer(void* _buffer, unsigned long long len)
        {
            uint8_t *buffer = (uint8_t*)_buffer; 

            if(IsEOF())
            {
                return nullptr;
            }

            for(unsigned long long i = 0; i < len; i++)
            {
                dataBuffer[dataCursor+i] = buffer[i];
            }

            dataCursor += len;

            return _buffer;
        }
    };

}