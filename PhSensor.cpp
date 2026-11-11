#include "PhSensor.h"
#include <Arduino.h>

const Event PhSensor::PH_READ_EVENT = Event(PH_READ_EVENT_ID);

PhSensor::PhSensor(int pin, EventHandler* eventHandler)
    : Sensor(pin, eventHandler) {
    pinMode(pin, INPUT);
}

float PhSensor::readPh() {
    int adcVal = analogRead(pin);
    return (adcVal / 4095.0f) * 14.0f;
}
