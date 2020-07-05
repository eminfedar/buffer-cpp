#ifndef FDR_BUFFER_HPP
#define FDR_BUFFER_HPP

#include <stdint.h>
#include <string.h>

class Buffer
{
public:
    explicit Buffer(int size)
    {
        this->data = new char[size];
    }
    ~Buffer()
    {
        delete this->data;
    }

    int32_t readInt32(int offset)
    {
        return (int32_t)this->data[offset];
    }
    int16_t readInt16(int offset)
    {
        return (int16_t)this->data[offset];
    }
    int8_t readInt8(int offset)
    {
        return (int8_t)this->data[offset];
    }

    void writeInt32(uint32_t number, int offset = -1)
    {
        int offsetReal = offset == -1 ? length : offset;

        memcpy(this->data + offsetReal, &number, 4);
        this->length += 4;
    }
    void writeInt16(uint16_t number, int offset = -1)
    {
        int offsetReal = offset == -1 ? length : offset;

        memcpy(this->data + offsetReal, &number, 2);
        this->length += 2;
    }
    void writeInt8(uint8_t number, int offset = -1)
    {
        int offsetReal = offset == -1 ? length : offset;

        memcpy(this->data + offsetReal, &number, 1);
        this->length += 1;
    }
    void write(const char* buffer, uint32_t length, int offset = -1)
    {
        int offsetReal = offset == -1 ? this->length : offset;
        memcpy(this->data + offsetReal, buffer, length);
        this->length += length;
    }

    uint32_t size() { return length; }
    const char* buffer() { return data; }

private:
    char *data;
    uint32_t length = 0;
};

#endif