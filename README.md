# CrcXX
A generic implementation of the CRC algorithm using Boost. 

Example usage:

```
#include "CrcXX.h"
#include <iostream>

int main() {
    std::string input = "Hello world!";
    std::string crc = Utils::crcXX<std::string>(input);
    std::cout << "CRC32 of \"" << input << "\": " << crc << std::endl;
    
    const char data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    unsigned int crc2 = Utils::crcXX<unsigned int, 16>(data, sizeof(data));
    std::cout << "CRC16 of {0x01, 0x02, 0x03, 0x04, 0x05}: " << crc2 << std::endl;
    
    std::string input2 = "Boost is awesome!";
    unsigned short crc3 = Utils::crcXX<unsigned short, 32>(input2);
    std::cout << "CRC32 of \"" << input2 << "\": " << crc3 << std::endl;
    
    const char data2[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    std::string crc4 = Utils::crcXX<std::string, 16>(data2, sizeof(data2));
    std::cout << "CRC16 of {0x01, 0x02, 0x03, 0x04, 0x05}: " << crc4 << std::endl;

    return 0;
}
```

Output:

```
CRC32 of "Hello world!": 1b851995
CRC16 of {0x01, 0x02, 0x03, 0x04, 0x05}: 47886
CRC32 of "Boost is awesome!": 23888
CRC16 of {0x01, 0x02, 0x03, 0x04, 0x05}: bb0e
```
