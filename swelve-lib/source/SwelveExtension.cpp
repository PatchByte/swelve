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
        this->OnUnload();

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

    SwelveHash SwelveExtension::GetIdentifier()
    {
        return identifier;
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
        SwelveHash identifier = 0;

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

        parsedExt->identifier = *extensionStream.Read(&identifier);
        parsedExt->OnLoad();

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
        
        // for desc length
        neededSize += strlen(input->description);

        // for identifier
        neededSize += sizeof(SwelveHash);

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
        SwelveHash identifier = input->identifier;

        if(nameLength == 0xFF || descriptionLength == 0xFF)
        {
            return false;
        }

        extensionStream.Write(nameLength);
        extensionStream.WriteRawBuffer((void*)input->name, nameLength);
        extensionStream.Write(descriptionLength);

        if(descriptionLength)
        {
            extensionStream.WriteRawBuffer((void*)input->description, descriptionLength);
        }

        extensionStream.Write(identifier);

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
            sizeof(uint64_t)    + 
            sizeof(SwelveHash)  * input->entries.size()
        );
    }

    bool SwelveWriter::WriteManifest(SwelveManifest* input, SwelveStream& manifestStream)
    {
        uint64_t entriesSize = input->entries.size();

        manifestStream.Write(entriesSize);

        for(auto currentEntry : input->entries)
        {
            manifestStream.Write(currentEntry.first);
        }

        return true;
    }

    SwelveManifest* SwelveReader::ReadManfiest(SwelveStream& extensionStream, SwelveManifestResolveCallback* resolveCallback)
    {
        SwelveManifest* manifest = new SwelveManifest();

        uint64_t entriesSize = 0;

        extensionStream.Read(&entriesSize);

        for(uint64_t i = 0; i < entriesSize; i++)
        {
            SwelveHash currentEntry = 0;

            extensionStream.Read(&currentEntry);

            manifest->entries[currentEntry] = resolveCallback(currentEntry);
        }

        return manifest;
    }
}