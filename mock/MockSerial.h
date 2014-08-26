#include <iostream>

class MockSerial {
public:
  void begin(unsigned long);
  void end();
  size_t write(const unsigned char*, size_t);
};

extern MockSerial Serial;
