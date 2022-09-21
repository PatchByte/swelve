#include "SwelveExtension.hpp"
#include "SwelveManifest.hpp"

namespace swelve
{

    SwelveExtension::SwelveExtension():
        name(nullptr),
        description(nullptr),
        allowDeallocationOfName(true),
        allowDeallocationOfDesc(true)
    {
    }

    SwelveExtension::~SwelveExtension()
    {
        if(name && allowDeallocationOfName)
        {
            delete[] name;
            name = nullptr;
        }

        if(description && allowDeallocationOfDesc)
        {
            delete[] description;
            description = nullptr;
        }
    }

    const char* SwelveExtension::GetName()
    {
        return name;
    }

    const char* SwelveExtension::GetDescription()
    {
        return description;
    }

    void* SwelveExtension::GetAdditionalInformations()
    {
        return nullptr;
    }

    SwelveHash SwelveExtension::GetAdditionalFlags()
    {
        return SwelveExtensionBaseFlags_BaseExtension;
    }

    /*
        Swelve Extension Binary Layout
        nameLength: u8
        name: u8 [@nameLength]
        descriptionLength: u8
        description: u8 [@descriptionLength]

        description and name are without a null terminator!
    */

    // Swelve Reader for reading extension

    SwelveExtension* SwelveReader::ReadExtension(SwelveStream& extensionStream)
    {
        SwelveExtension* parsedExt = new SwelveExtension();

        uint8_t nameLength = 0;
        uint8_t descriptionLength = 0;

        extensionStream.Read(&nameLength);

        if(nameLength)
        {
            parsedExt->name = new char[nameLength + 1];
            memset((void*)parsedExt->name, 0, nameLength + 1);
            extensionStream.ReadRawBuffer((void*)parsedExt->name, nameLength);
        }
        else
        {
            delete parsedExt;
            return nullptr;
        }

        extensionStream.Read(&descriptionLength);

        if(descriptionLength)
        {
            parsedExt->description = new char[descriptionLength + 1];
            memset((void*)parsedExt->description, 0, descriptionLength + 1);
            extensionStream.ReadRawBuffer((void*)parsedExt->description, descriptionLength);
        }
        else
        {
            parsedExt->description = nullptr;
        }

        return parsedExt;
    }

    // Swelve Writer for writing extensions

    size_t SwelveWriter::GetExtensionWriteSize(SwelveExtension* input)
    {
        size_t neededSize = 0;

        // for size of length
        neededSize += sizeof(uint8_t) * 2;

        // for name length
        neededSize += strlen(input->name);
        neededSize += strlen(input->description);

        return neededSize;
    }

    bool SwelveWriter::WriteExtension(SwelveExtension* input, SwelveStream& extensionStream)
    {
        if(!input->name || !input->description)
        {
            return false;
        }

        uint8_t nameLength = (uint8_t) strlen(input->name);
        uint8_t descriptionLength = (uint8_t) strlen(input->description);

        if(nameLength == 0xFF || descriptionLength == 0xFF)
        {
            return false;
        }

        extensionStream.Write(&nameLength);
        extensionStream.WriteRawBuffer((void*)input->name, nameLength);
        extensionStream.Write(&descriptionLength);

        if(descriptionLength)
        {
            extensionStream.WriteRawBuffer((void*)input->description, descriptionLength);
        }

        return true;
    }

    // Swelve Writer for Manifest

    /*
        Swelve Manifest
        manifestEntriesCount: u64
        manifestEntries: ManfiestEntry[@manifestEntriesCount]

        Swelve Manifest Entry
        manifestIdentifier: u64
    */

    size_t SwelveWriter::GetManifestWriteSize(SwelveManifest* input)
    {
        return (
            sizeof(uint64_t) + 
            sizeof(uint64_t) * input->entries->size()
        );
    }

    bool SwelveWriter::WriteManifest(SwelveManifest* input, SwelveStream& manifestStream)
    {
        uint64_t entriesSize = input->entries->size();

        manifestStream.Write(entriesSize);

        for(SwelveManifestEntry* currentEntry : *input->entries)
        {
            manifestStream.Write(currentEntry->linkedIdentifier);
        }

        return true;
    }
}