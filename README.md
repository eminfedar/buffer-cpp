# buffer-cpp
Header only Buffer class for C++.

# Why?
I made this for making Socket read-write operations easy.

## - Writing to a buffer:
```cpp
#include "Buffer.hpp"

int a = 0xFFFFFFFF;
short b = 0xAAAA;
char c = 0xCC;

Buffer buffer(50); // Allocate 50 bytes

// Write them to the buffer:
buffer.writeInt32(a);
buffer.writeInt16(b);
buffer.writeInt8(c);

// Get buffer data (const char*) and size:
buffer.buffer(); // const char* = {0xFF, 0xFF, 0xFF, 0xFF, 0xAA, 0xAA, 0xCC};
buffer.size(); // 7 bytes

// You can write a char* to Buffer directly:
char str[] = "Hi there!";
buffer.write(str, 9);
```
## - Reading from a buffer:
```cpp
// Use already written buffer above:
buffer.buffer(); // const char* = {0xFF, 0xFF, 0xFF, 0xFF, 0xAA, 0xAA, 0xCC

int   a = buffer.readInt32(0);  // [0-3] {0xFF, 0xFF, 0xFF, 0xFF}
short b = buffer.readInt16(4);  // [4-5] {0xAA, 0xAA}
char  c = buffer.readInt8(6);   // [6]   {0xCC}
```
