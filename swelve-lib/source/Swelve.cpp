#include "Swelve.hpp"
#include "SwelveExtension.hpp"

namespace swelve
{
    SwelveInstance::SwelveInstance():
        swelveExtensionList(new std::vector<SwelveExtension*>())
    {
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

    SwelveExtension* SwelveInstance::ParseExtension(SwelveStream& extensionStream)
    {
        SwelveReader* reader = this->CreateReader();
        SwelveExtension* ext = reader->ReadExtension(extensionStream);

        AppendExtension(ext);

        return ext;
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