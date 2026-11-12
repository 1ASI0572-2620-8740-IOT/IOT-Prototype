#ifndef TELEMETRY_DEVICE_H
#define TELEMETRY_DEVICE_H

#include "Device.h"
#include "PhSensor.h"
#include "TemperatureSensor.h"
#include "LcdDisplay.h"
#include "Led.h"
#include "ServoActuator.h"
#include "CloudClient.h"
#include <esp_system.h>

/**
 * @brief Dispositivo de telemetría: lee pH y temperatura, muestra en LCD y Serial.
 *        Enciende LED verde si pH (6-8) y temp (20-30°C) están en rango; rojo en caso contrario.
 */
class TelemetryDevice : public Device {
private:
    PhSensor phSensor;
    TemperatureSensor tempSensor;
    LcdDisplay lcd;
    Led greenLed;
    Led redLed;
    ServoActuator servo;
    CloudClient cloud;
    float phVal;
    float tempVal;
    bool lastOk;
    bool hasLastOk;
    char bootId[24];
    uint32_t telemetryCounter;

public:
    static const int PH_PIN = 34;          ///< Pin analógico del potenciómetro (pH).
    static const int TEMP_PIN = 4;         ///< Pin digital del DS18B20.
    static const int GREEN_LED_PIN = 2;    ///< LED verde (rango correcto).
    static const int RED_LED_PIN = 5;      ///< LED rojo (fuera de rango).
    static const int SERVO_PIN = 18;       ///< Servo de cierre de emergencia.

    TelemetryDevice();

    void on(Event event) override;         ///< Maneja eventos de sensores.
    void handle(Command command) override; ///< Maneja comandos del display y LEDs.

    void begin(); ///< Inicializa sensores y display.

    void triggerPhReadEvent();   ///< Dispara la lectura de pH.
    void triggerTempReadEvent(); ///< Dispara la lectura de temperatura.

    void evaluateRanges(); ///< Evalúa rangos y actualiza LEDs.

    String getMeasuredAt(); ///< Timestamp ISO 8601 UTC.

    float getPh() const;
    float getTemp() const;

    LcdDisplay& getLcd();
    Led& getGreenLed();
    Led& getRedLed();
    ServoActuator& getServo();
};

#endif // TELEMETRY_DEVICE_H
