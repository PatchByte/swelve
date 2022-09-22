#include "main.hpp"

void test::ReadWriteExtensions()
{
    uint8_t *exampleSerializedInput = nullptr;
    size_t exampleExtensionSerializedSize = 0;

    swelve::SwelveInstance* swelveInstance = new swelve::SwelveInstance();

    swelve::SwelveExtension* exampleWrittenExtension = nullptr;
    swelve::SwelveExtension* exampleReadedExtension = nullptr;

    swelve::SwelveReader* exampleReader = swelveInstance->CreateReader();
    swelve::SwelveWriter* exampleWriter = swelveInstance->CreateWriter();

    srand((uint32_t)time(0));

    {
        exampleWrittenExtension = new swelve::SwelveExtension();

        exampleWrittenExtension->allowDeallocationOfDesc = false;
        exampleWrittenExtension->allowDeallocationOfName = false;

        exampleWrittenExtension->name = "Test Extension";
        exampleWrittenExtension->description = "Just a simple test.";

        exampleWrittenExtension->identifier = 0xdeadbeef;

        exampleExtensionSerializedSize = exampleWriter->GetExtensionWriteSize(exampleWrittenExtension);
        exampleSerializedInput = new uint8_t[exampleExtensionSerializedSize];

        swelve::SwelveStream exampleOutputStream = swelve::SwelveStream(exampleSerializedInput, exampleExtensionSerializedSize);

        std::cout << "[ Extension::WriterTest ] Needed Write Size: " << std::format("{:08x}", exampleExtensionSerializedSize) << std::endl;

        exampleWriter->WriteExtension(exampleWrittenExtension, exampleOutputStream);

        std::ofstream ostream; 
        ostream.open("example_extension_output.bin", std::ios::binary | std::ios::trunc);
        ostream.write((char*)exampleSerializedInput, exampleExtensionSerializedSize);
        ostream.close();

        delete exampleWrittenExtension;
    }

    {
        swelve::SwelveStream exampleInputStream = swelve::SwelveStream(exampleSerializedInput, exampleExtensionSerializedSize);
        exampleReadedExtension = swelveInstance->ParseExtension(exampleInputStream);

        if(exampleReadedExtension)
        {
            std::cout << "[ Extension::ReaderTest ]" << std::format("\n\tName: {}\n\tDescription: {}\n\tIdentifier: {:016x}", exampleReadedExtension->name, exampleReadedExtension->description, exampleReadedExtension->identifier) << std::endl; 
            delete exampleReadedExtension;
        }
        else
        {
            std::cout << "[ Extension::ReaderTest ] Failed to read Extension." << std::endl;
        }
    }
    
    delete[] exampleSerializedInput;

    delete exampleWriter;
    delete exampleReader;

    delete swelveInstance;
}