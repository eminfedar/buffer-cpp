# buffer-cpp
Header only Buffer class for C++.

## Examples:
### Writing to a buffer:
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
buffer.buffer(); // {0xFF, 0xFF, 0xFF, 0xFF, 0xAA, 0xAA, 0xCC}

// You can write with offsets too:
buffer.writeInt32(a, 0);
buffer.writeInt16(b, 6);
buffer.writeInt8(c, 10);
buffer.buffer(); // {0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 0xAA, 0xAA, 0, 0, 0xCC}

// Get buffer data:
buffer.buffer(); // const char* = {0xFF, 0xFF, 0xFF, 0xFF, 0xAA, 0xAA, 0xCC};
buffer.size(); // 7 bytes
```
Writing char arrays to buffer:
```cpp
// You can write a char array to Buffer directly:
char str1[] = "Hi there!";
buffer.write(str1, strlen(str1));

char str2[] = "Another sentence.";
buffer.write(str2, strlen(str2), 15); // offset: 15

buffer.buffer(); // "Hi there!______Another sentence._____________" (50 length buffer.)
```
### Reading from a buffer:
```cpp
// Use already written buffer above:
buffer.buffer(); // const char* = {0xFF, 0xFF, 0xFF, 0xFF, 0xAA, 0xAA, 0xCC}

int   a = buffer.readInt32(0);  // [0-3] {0xFF, 0xFF, 0xFF, 0xFF}
short b = buffer.readInt16(4);  // [4-5] {0xAA, 0xAA}
char  c = buffer.readInt8(6);   // [6]   {0xCC}
```
