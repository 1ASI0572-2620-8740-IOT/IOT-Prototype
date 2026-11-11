#include "TemperatureSensor.h"
#include <Arduino.h>

const Event TemperatureSensor::TEMP_READ_EVENT = Event(TEMP_READ_EVENT_ID);

TemperatureSensor::TemperatureSensor(int pin, EventHandler* eventHandler)
    : Sensor(pin, eventHandler), oneWire(pin), sensors(&oneWire) {}

void TemperatureSensor::begin() {
    sensors.begin();
}

float TemperatureSensor::readTemp() {
    sensors.requestTemperatures();
    float temp = sensors.getTempCByIndex(0);
    if (temp == DEVICE_DISCONNECTED_C) {
        Serial.println("[TemperatureSensor] DS18B20 desconectado o sin respuesta");
    }
    return temp;
}
