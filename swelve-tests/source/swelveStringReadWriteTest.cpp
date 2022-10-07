#include "main.hpp"

void test::ReadWriteString()
{
    std::function<const char*()> allocatedRandomName = []() -> const char*
    {
        constexpr size_t genNameLength = 0x20;
        char* genName = (char*) malloc(genNameLength + 1);

        memset(genName, 0, genNameLength + 1);

        for(size_t i = 0; i < genNameLength; i++)
        {
            genName[i] = 'a' + (rand() % ('z' - 'a'));
        }

        return genName;
    };

    std::cout << "[ String::ReadWriteTest ]" << std::endl;
    
    for(int i = 0; i < 10; i++)
    {
        const char* randomExportString = allocatedRandomName();

        swelve::SwelveString serializableString = randomExportString;
        swelve::SwelveString deserializedString = swelve::SwelveString();
        swelve::SwelveObject serializedString = swelve::SwelveObject(&serializableString);
        swelve::SwelveStream serializedStringStream = serializedString.Stream();

        deserializedString.Import(serializedStringStream);

        std::cout << "\t" << std::format("[{}] == [{}]", randomExportString, deserializedString.str) << std::endl;

        free((void*)randomExportString);
    }
}