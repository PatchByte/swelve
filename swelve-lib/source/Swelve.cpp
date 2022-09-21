#include "Swelve.hpp"
#include "SwelveExtension.hpp"

namespace swelve
{
    SwelveInstance::SwelveInstance()
    {
        this->swelveExtensionList = new std::vector<SwelveExtension*>();
    }

    SwelveInstance::~SwelveInstance()
    {
        if(this->swelveExtensionList)
        {
            delete this->swelveExtensionList;
            this->swelveExtensionList = nullptr;
        }
    }

    SwelveReader* SwelveInstance::CreateReader()
    {
        return new SwelveReader();
    }

    SwelveWriter* SwelveInstance::CreateWriter()
    {
        return new SwelveWriter();
    }

    bool SwelveInstance::ParseExtension(SwelveStream& extensionStream)
    {
        SwelveReader* reader = this->CreateReader();

        AppendExtension(reader->ReadExtension(extensionStream));

        return reader;
    }

    bool SwelveInstance::AppendExtension(SwelveExtension* extension)
    {
        if(extension)
        {
            
            this->swelveExtensionList->push_back(extension);

            return true;
        }

        return false;
    }
}