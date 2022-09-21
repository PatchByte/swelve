#include "main.hpp"

#include <functional>

void test::ReadWriteManifest()
{
    std::function<uint64_t()> randomULL = []() -> uint64_t
    {
        srand((unsigned int) time(0));

        std::vector<uint8_t> _rand = { };
        for(unsigned i = 0; i < 8; i ++)
        { _rand.push_back(rand() % 0xFF); }

        return *(uint64_t*)_rand.data();
    };

    std::cout << "Random 8 Byte Value: " << std::format("{:016x}", randomULL()) << std::endl;
}