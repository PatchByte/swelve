#pragma once

namespace swelve
{

    class SwelveStream
    {
    private:
        void* pData;
        unsigned long long mCursor;
        unsigned long long mMaxSize;
    public:
        SwelveStream(void* data, unsigned long long dataLength)
        {
            pData = data;
            mCursor = 0;
            mMaxSize = dataLength;
        }

        unsigned long long GetCursor()
        {
            return mCursor;
        }

        unsigned long long GetSizeOfData()
        {
            return mMaxSize;
        }

        void SetCursor(unsigned long long pos)
        {
            mCursor = pos;
        }

        void AddCursor(unsigned long long pos)
        {
            mCursor = mCursor + pos;
        }

        void SubCursor(unsigned long long pos)
        {
            mCursor = mCursor - pos;
        }

        bool IsEOF()
        {
            return mCursor >= mMaxSize;
        }

        template<typename T>
        T* Read(T* buffer)
        {
            if(IsEOF())
            {
                return nullptr;
            }

            for(unsigned long long i = 0; i < sizeof(T); i++)
            {
                ((unsigned char*)buffer)[i] = ((unsigned char*)pData)[mCursor+i];
            }

            mCursor = mCursor + sizeof(T);

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
                ((unsigned char*)pData)[mCursor+i] = ((unsigned char*)buffer)[i];
            }

            mCursor = mCursor + sizeof(T);

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
                ((unsigned char*)buffer)[i] = ((unsigned char*)pData)[mCursor+i];
            }

            mCursor = mCursor + len;

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
                ((unsigned char*)pData)[mCursor+i] = ((unsigned char*)buffer)[i];
            }

            mCursor = mCursor + len;

            return buffer;
        }
    };

}