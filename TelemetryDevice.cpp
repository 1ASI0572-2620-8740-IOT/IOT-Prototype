#include "TelemetryDevice.h"
#include <Arduino.h>

TelemetryDevice::TelemetryDevice()
    : phSensor(PH_PIN, this),
      tempSensor(TEMP_PIN, this),
      lcd(0x27, 16, 2, this),
      greenLed(GREEN_LED_PIN, false, this),
      redLed(RED_LED_PIN, false, this),
      servo(SERVO_PIN, this),
      phVal(0.0f),
      tempVal(0.0f),
      lastOk(false),
      hasLastOk(false) {}

void TelemetryDevice::begin() {
    tempSensor.begin();
    lcd.begin();
    servo.begin();
    evaluateRanges(); // Estado inicial (fuera de rango -> rojo + cierre)
}

void TelemetryDevice::on(Event event) {
    if (event == PhSensor::PH_READ_EVENT) {
        phVal = phSensor.readPh();
        lcd.setPh(phVal);
        lcd.handle(LcdDisplay::UPDATE_DISPLAY_COMMAND);

        Serial.print("pH Medido: ");
        Serial.print(phVal, 2);
        Serial.println();

        evaluateRanges();
    } else if (event == TemperatureSensor::TEMP_READ_EVENT) {
        tempVal = tempSensor.readTemp();
        lcd.setTemp(tempVal);
        lcd.handle(LcdDisplay::UPDATE_DISPLAY_COMMAND);

        Serial.print("Temp Medida: ");
        Serial.print(tempVal, 2);
        Serial.println(" C");

        evaluateRanges();
    }
}

void TelemetryDevice::handle(Command command) {
    if (command == LcdDisplay::UPDATE_DISPLAY_COMMAND) {
        Serial.printf("Display actualizado -> pH: %.2f | Temp: %.2f C\n", phVal, tempVal);
    } else if (command == Led::TURN_ON_COMMAND || command == Led::TURN_OFF_COMMAND || command == Led::TOGGLE_LED_COMMAND) {
        // Comandos propagados por los LEDs (logging opcional)
    }
}

void TelemetryDevice::triggerPhReadEvent() {
    phSensor.on(PhSensor::PH_READ_EVENT);
}

void TelemetryDevice::triggerTempReadEvent() {
    tempSensor.on(TemperatureSensor::TEMP_READ_EVENT);
}

void TelemetryDevice::evaluateRanges() {
    bool ok = (phVal >= 6.0f && phVal <= 8.0f &&
               tempVal >= 20.0f && tempVal <= 30.0f);

    if (!hasLastOk || ok != lastOk) {
        Serial.printf("Estado: %s (pH=%.2f, Temp=%.2f)\n",
                      ok ? "EN RANGO" : "FUERA DE RANGO", phVal, tempVal);
        hasLastOk = true;
        lastOk = ok;
    }

    if (ok) {
        greenLed.handle(Led::TURN_ON_COMMAND);
        redLed.handle(Led::TURN_OFF_COMMAND);
        servo.handle(ServoActuator::OPEN_COMMAND);
    } else {
        greenLed.handle(Led::TURN_OFF_COMMAND);
        redLed.handle(Led::TURN_ON_COMMAND);
        servo.handle(ServoActuator::CLOSE_COMMAND);
    }
}

float TelemetryDevice::getPh() const { return phVal; }
float TelemetryDevice::getTemp() const { return tempVal; }
LcdDisplay& TelemetryDevice::getLcd() { return lcd; }
ServoActuator& TelemetryDevice::getServo() { return servo; }
Led& TelemetryDevice::getGreenLed() { return greenLed; }
Led& TelemetryDevice::getRedLed() { return redLed; }
