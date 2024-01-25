#include "Sensor.hpp"

Sensor::Sensor(byte address, TwoWire* wire) : deviceAddress(address), wireObject(wire) {
    // Geen specifieke initialisatie nodig in dit voorbeeld
}

bool Sensor::isConnected() {
    wireObject->beginTransmission(deviceAddress);
    byte error = wireObject->endTransmission();

    return (error == 0);
}
