#ifndef digitalio_h
#define digitalio_h
#include <Arduino.h>

#define sizedArray(x) x, sizeof(x)

#define bitMasked(x)  (digitalPinToBitMask(address[x]))
#define portReg(x)    (*(portOutputRegister(digitalPinToPort(address[x]))))
#define pinReg(x)     (*(portInputRegister(digitalPinToPort(address[x]))))

class DigitalIO{
  const uint8_t* address;
  uint8_t total;

  public: DigitalIO(){}
  
  public: DigitalIO(const uint8_t* address, const uint8_t total, const uint8_t mode) {
    this->address = address;
    this->total = total;
    for (uint8_t i = 0; i < total; i++) {
      pinMode(address[i], mode);
    }
  }

  public: uint8_t getTotalPin() {
    return total;
  }
  
  public: void set(const uint8_t indexPin) {
    portReg(indexPin) |= bitMasked(indexPin);
  }
  
  public: void clear(const uint8_t indexPin) {
    portReg(indexPin) &= ~bitMasked(indexPin);
  }
  
  public: void toggle(const uint8_t indexPin) {
    portReg(indexPin) ^= bitMasked(indexPin);
  }
  
  public: void write(const uint8_t indexPin, const uint8_t theLogic) {
    if (theLogic) portReg(indexPin) |= bitMasked(indexPin);
    else portReg(indexPin) &= ~bitMasked(indexPin);
  }

  public: void writes(uint16_t data) {
    for (uint8_t i = 0; i < total; i++) {
      if (data & 1) portReg(i) |= bitMasked(i);
      else portReg(i) &= ~bitMasked(i);
      data >>= 1;
    }
  }
  
  public: void writes(uint8_t data) {
    for (uint8_t i = 0; i < total; i++) {
      if (data & 1) portReg(i) |= bitMasked(i);
      else portReg(i) &= ~bitMasked(i);
      data >>= 1;
    }
  }
  
  public: void digitalIOMode(const uint8_t mode) {
    for (uint8_t i = 0; i < total; i++) {
      pinMode(address[i], mode);
    }
  }
  
  public: boolean read(const uint8_t indexPin) {
    return pinReg(indexPin) & bitMasked(indexPin);
  }

  public: uint8_t read() {
    retVar = 0;
    for (uint8_t i = 0; i < total; i++) {
      retVar <<= 1;
      if (pinReg(i) & bitMasked(i)) retVar |= 1;
    }
    return retVar;
  }

  public: uint8_t readInv() {
    uint8_t retVar = 0;
    for (uint8_t i = 0; i < 4; i++) {
      retVar <<= 1;
      if (!(pinReg(i) & bitMasked(i))) retVar |= 1;
    }
    return retVar;
  }
  
};
#endif