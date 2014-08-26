#include <cstring>
#include <iostream>
#include <iomanip>

#include "MockSerial.h"

void MockSerial::begin(unsigned long speed) {
  return;
}

void MockSerial::end() {
  return;
}

size_t MockSerial::write( const unsigned char buf[], size_t size ) {
  using namespace std;
  ios_base::fmtflags oldFlags = cout.flags();
  streamsize oldPrec = cout.precision();
  char oldFill = cout.fill();

  cout << "Serial::write: ";
  cout << internal << setfill('0');

  for( unsigned int i = 0; i < size; i++ ){
    cout << setw(2) << hex << (unsigned int)buf[i] << " ";
  }
  cout << endl;

  cout.flags(oldFlags);
  cout.precision(oldPrec);
  cout.fill(oldFill);

  return size;
}

MockSerial Serial
