#ifndef FDR_BUFFER_HPP
#define FDR_BUFFER_HPP

#include <cstdint>
#include <cstring>
#include <iostream>
#include <stdexcept>

class Buffer {
public:
    // Constructor
    explicit Buffer(int n)
        : data(new char[n] { 0 }), bufferCapacity(n)
    {
    }

    // Deconstructor
    ~Buffer() { delete[] data; }

    // Copy Constructor
    Buffer(const Buffer& other_bfr)
    {
        data = new char[other_bfr.capacity()];
        bufferLength = other_bfr.length();
        bufferCapacity = other_bfr.capacity();

        std::memcpy(data, other_bfr.buffer(), other_bfr.length());
    }

    // Copy assignment
    Buffer& operator=(const Buffer& other_bfr)
    {
        if (this == &other_bfr)
            return *this;

        delete[] data;
        
        data = new char[other_bfr.capacity()];
        bufferLength = other_bfr.length();
        bufferCapacity = other_bfr.capacity();

        std::memcpy(data, other_bfr.buffer(), other_bfr.length());

        return *this;
    }

    // Move Constructor
    Buffer(Buffer&& other_bfr)
    {
        data = other_bfr.buffer();
        bufferLength = other_bfr.length();
        bufferCapacity = other_bfr.capacity();

        *other_bfr.bufferMutable() = nullptr;
    }

    // Move Assignment
    Buffer& operator=(Buffer&& other_bfr)
    {
        data = other_bfr.buffer();
        bufferLength = other_bfr.length();
        bufferCapacity = other_bfr.capacity();

        *other_bfr.bufferMutable() = nullptr;

        return *this;
    }

    // -- Methods
    template <typename T>
    T read(std::size_t const offset)
    {
        if (offset + sizeof(T) >= bufferCapacity || offset < 0)
            throw std::length_error("Can't read out of bounds");

        return static_cast<T>(data[offset]);
    }

    template <typename T>
    void write(T const value, std::size_t const _offset = SIZE_MAX)
    {
        std::size_t offset = (_offset == SIZE_MAX) ? bufferLength : _offset;

        if (offset < 0)
            throw std::length_error("Can't write to a negative offset");

        if (offset + sizeof(T) >= bufferCapacity)
            allocateBiggerMemory<T>(offset + sizeof(T));

        std::memcpy(data + offset, &value, sizeof(T));

        if (bufferLength < offset)
            bufferLength = offset;
    }

    std::size_t length() const { return bufferLength; }
    std::size_t capacity() const { return bufferCapacity; }
    char* buffer() const { return data; }
    char** bufferMutable() { return &data; }

protected:
    char* data;
    std::size_t bufferLength = 0;
    std::size_t bufferCapacity = 0;

private:
    template <typename T>
    void allocateBiggerMemory(std::size_t offset)
    {
        // allocate new & bigger memory
        bufferCapacity = (offset + sizeof(T)) * 2;
        char* new_buffer = new char[bufferCapacity];

        delete[] data;
        data = new_buffer;
    }
};

#endif
