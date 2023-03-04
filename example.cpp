#include "Buffer.hpp"

int main()
{
    uint32_t a = 0xFFFFFFFF;
    uint16_t b = 0xAAAA;
    uint8_t c = 0xCC;

    Buffer buffer(50); // Allocate 50 bytes

    // Write them to the buffer:
    buffer.write<std::uint32_t>(a);
    buffer.write<std::uint16_t>(b);
    buffer.write<std::uint8_t>(c);
    buffer.buffer(); // {0xFF, 0xFF, 0xFF, 0xFF, 0xAA, 0xAA, 0xCC}

    // You can write with offsets too:
    buffer.write<std::uint32_t>(a, 0);
    buffer.write<std::uint16_t>(b, 6);
    buffer.write<std::uint8_t>(c, 10);
    buffer.buffer(); // {0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 0xAA, 0xAA, 0, 0, 0xCC}

    // Get buffer data:
    buffer.buffer(); // const char* = {0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 0xAA, 0xAA,
                     // 0, 0, 0xCC};
    buffer.length(); // 10

    for (std::size_t i = 0; i < buffer.length(); i += sizeof(uint16_t)) {
        std::cout << buffer.read<uint16_t>(i) << " ,";
    }
    std::cout << "\n";

    std::cout << "Buffer length is:" << buffer.length() << "\n";
    std::cout << "Buffer capacity is:" << buffer.capacity() << "\n";

    /* output:
    65535 ,65535 ,0 ,65450 ,0 ,
    Buffer length is:10
    Buffer capacity is:50
    */
}
