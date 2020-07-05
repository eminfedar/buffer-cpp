#ifndef FDR_BUFFER_HPP
#define FDR_BUFFER_HPP

#include <stdint.h>
#include <string.h>

class Buffer
{
public:
    explicit Buffer(int size)
    {
        this->data = new char[size]{0};
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

    void writeInt32(int32_t number, int offset = -1)
    {        
        int appendOffset = offset == -1 ? length : offset;

        memcpy(this->data + appendOffset, &number, sizeof(int32_t));

        if (appendOffset + sizeof(int32_t) > this->length)
            this->length = appendOffset + sizeof(int32_t);        
    }
    void writeInt16(int16_t number, int offset = -1)
    {
        int appendOffset = offset == -1 ? length : offset;

        memcpy(this->data + appendOffset, &number, sizeof(int16_t));

        if (appendOffset + sizeof(int16_t) > this->length)
            this->length = appendOffset + sizeof(int16_t);  
    }
    void writeInt8(int8_t number, int offset = -1)
    {
        int appendOffset = offset == -1 ? length : offset;

        memcpy(this->data + appendOffset, &number, sizeof(int8_t));

        if (appendOffset + sizeof(int8_t) > this->length)
            this->length = appendOffset + sizeof(int8_t);  
    }
    void write(const char* buffer, uint32_t length, int offset = -1)
    {        
        int appendOffset = offset == -1 ? this->length : offset;

        memcpy(this->data + appendOffset, buffer, length);

        if (appendOffset + length > this->length)
            this->length = appendOffset + length; 
    }

    uint32_t size() { return length; }
    const char* buffer() { return data; }

private:
    char *data;
    uint32_t length = 0;
};

#endif