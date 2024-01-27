#include "Sensor.hpp"

Sensor::Sensor(byte address, TwoWire* wire) : deviceAddress(address), wireObject(wire) {
  // Geen specifieke initialisatie nodig in dit voorbeeld
}
Sensor::Sensor(byte address, TwoWire* wire, int16_t inMinWaarde, int16_t inMaxWaarde) : deviceAddress(address), wireObject(wire), minWaarde(inMinWaarde), maxWaarde(inMaxWaarde) {

}

bool Sensor::isConnected() {
  wireObject->beginTransmission(deviceAddress);
  byte error = wireObject->endTransmission();

  return (error == 0);
}

byte Sensor::isCableConnected(int16_t waarde) {
  byte isConnected = 0;
  if (waarde <= maxWaarde && waarde >= minWaarde) {
    isConnected = 1;
  }
  return isConnected;
}

byte Sensor::howCableConnected(byte waarde) {
  byte isConnected = 0;
  if (waarde <= maxWaarde && waarde >= minWaarde) {
    isConnected = waarde;
  }
  return isConnected;
}
