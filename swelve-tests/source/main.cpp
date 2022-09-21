#include "main.hpp"

#include <swelve-lib/include/Swelve.hpp>
#include <swelve-lib/include/SwelveExtension.hpp>

#include <format>
#include <sstream>
#include <fstream>

int main(int argc, char const *argv[])
{
    uint8_t *exampleSerializedInput = nullptr;
    size_t exampleExtensionSerializedSize = 0;

    swelve::SwelveInstance* swelveInstance = new swelve::SwelveInstance();

    swelve::SwelveExtension* exampleWritedExtension = nullptr;
    swelve::SwelveExtension* exampleReadedExtension = nullptr;

    swelve::SwelveReader* exampleReader = swelveInstance->CreateReader();
    swelve::SwelveWriter* exampleWriter = swelveInstance->CreateWriter();

    {
        exampleWritedExtension = new swelve::SwelveExtension();

        exampleWritedExtension->allowDeallocationOfDesc = false;
        exampleWritedExtension->allowDeallocationOfName = false;

        exampleWritedExtension->name = "Test Extension";
        exampleWritedExtension->description = "Just a simple test.";

        exampleExtensionSerializedSize = exampleWriter->GetExtensionWriteSize(exampleWritedExtension);
        exampleSerializedInput = new uint8_t[exampleExtensionSerializedSize];

        swelve::SwelveStream exampleOutputStream = swelve::SwelveStream(exampleSerializedInput, exampleExtensionSerializedSize);

        std::cout << "[ Extension::WriterTest ] Needed Write Size: " << std::format("{:08x}", exampleExtensionSerializedSize) << std::endl;

        exampleWriter->WriteExtension(exampleWritedExtension, exampleOutputStream);

        std::ofstream ostream; 
        ostream.open("example_wrote_output.bin", std::ios::binary | std::ios::trunc);
        ostream.write((char*)exampleSerializedInput, exampleExtensionSerializedSize);
        ostream.close();

        delete exampleWritedExtension;
    }

    {
        swelve::SwelveStream exampleInputStream = swelve::SwelveStream(exampleSerializedInput, exampleExtensionSerializedSize);
        exampleReadedExtension = swelveInstance->ParseExtension(exampleInputStream);

        if(exampleReadedExtension)
        {
            std::cout << "[ Extension::ReaderTest ]" << std::format("\n\tName: {}\n\tDescription: {}", exampleReadedExtension->name, exampleReadedExtension->description); 
            delete exampleReadedExtension;
        }
        else
        {
            std::cout << "[ Extension::ReaderTest ] Failed to read Extension." << std::endl;
        }
    }
    
    delete exampleWriter;
    delete exampleReader;

    delete swelveInstance;

    return 0;
}
