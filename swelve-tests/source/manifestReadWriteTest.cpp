#include "main.hpp"

#include <functional>

static std::map<swelve::SwelveHash, swelve::SwelveExtension*> sGeneratedExtensions =
{
};

static void PopulateExtensionMap()
{
    std::function<const char*()> allocatedRandomName = []() -> const char*
    {
        constexpr size_t genNameLength = 10;
        char* genName = (char*) malloc(genNameLength + 1);

        memset(genName, 0, genNameLength + 1);

        for(size_t i = 0; i < genNameLength; i++)
        {
            genName[i] = 'a' + (rand() % ('z' - 'a'));
        }

        return genName;
    };

    sGeneratedExtensions = 
    {
        {
            0xdead,
            new swelve::SwelveExtension
        },
        {
            0xbeef,
            new swelve::SwelveExtension
        },
        {
            0xc0de,
            new swelve::SwelveExtension
        },
        {
            0xdec0de,
            new swelve::SwelveExtension
        },
        {
            0xfeed,
            new swelve::SwelveExtension
        }
    };

    for(auto currentEntry : sGeneratedExtensions)
    {
        currentEntry.second->identifier = currentEntry.first;

        currentEntry.second->allowDeallocationOfDesc = false;
        currentEntry.second->allowDeallocationOfName = true;

        currentEntry.second->description = "-.-";
        currentEntry.second->name = allocatedRandomName();

        std::cout << "\t\t" << std::format("[ {} ] : {:016x}", currentEntry.second->name, currentEntry.second->identifier) << std::endl;
    }
}

static swelve::SwelveExtension* EasyResolver(swelve::SwelveHash resvHash)
{
    return sGeneratedExtensions[resvHash]; 
}

void test::ReadWriteManifest()
{
    swelve::SwelveInstance* swelveInstance = new swelve::SwelveInstance();
    swelve::SwelveWriter* writer = swelveInstance->CreateWriter();
    swelve::SwelveReader* reader = swelveInstance->CreateReader();

    size_t writtenManifestBufferSize = 0;
    uint8_t* writtenManifestBuffer = nullptr;

    std::cout << "[ Manifest::Test ]" << std::endl;
    std::cout << "\t[ Manifest::PopulateExtensionMap ]" << std::endl;

    PopulateExtensionMap();
    
    {
        std::cout << "\t[ Manifest::WriteTest ]" << std::endl;

        swelve::SwelveManifest* writtenManifest = new swelve::SwelveManifest();

        writtenManifest->entries = sGeneratedExtensions;

        writtenManifestBufferSize = writer->GetManifestWriteSize(writtenManifest);
        writtenManifestBuffer = new uint8_t[writtenManifestBufferSize]; 

        swelve::SwelveStream writtenManifestStream = swelve::SwelveStream(writtenManifestBuffer, writtenManifestBufferSize);

        std::cout << "\t\t" << std::format("[ Manifest Buffer Size] :  0x{:02x}", writtenManifestBufferSize) << std::endl;

        writer->WriteManifest(writtenManifest, writtenManifestStream);

        std::ofstream ostream; 
        ostream.open("example_manifest_output.bin", std::ios::binary | std::ios::trunc);
        ostream.write((char*)writtenManifestBuffer, writtenManifestBufferSize);
        ostream.close();

        delete writtenManifest;
    }
    {
        std::cout << "\t[ Manifest::ReadTest ]" << std::endl;

        swelveInstance->PushResolveCallback(EasyResolver);

        swelve::SwelveStream readedManifestStream = swelve::SwelveStream(writtenManifestBuffer, writtenManifestBufferSize);
        swelve::SwelveManifest* readedManifest = swelveInstance->ParseManifest(readedManifestStream);

        for(auto currentEntry : swelveInstance->swelveExtensionMap)
        {
            std::cout << "\t\t" << std::format("[ {} ] : {:016x}", currentEntry.second->name, currentEntry.second->identifier) << std::endl;
        }
    }

    for(auto currentExtensionEntry : sGeneratedExtensions)
    {
        delete currentExtensionEntry.second;
    }

    sGeneratedExtensions.clear();

    delete[] writtenManifestBuffer;

    delete reader;
    delete writer;
    delete swelveInstance;

    std::cout << "\t[ Manifest::Cleanup ]" << std::endl;
}