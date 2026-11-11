#ifndef TEMPERATURE_SENSOR_H
#define TEMPERATURE_SENSOR_H

#include "Sensor.h"
#include <OneWire.h>
#include <DallasTemperature.h>

/**
 * @brief Sensor de temperatura basado en DS18B20 (OneWire).
 */
class TemperatureSensor : public Sensor {
private:
    OneWire oneWire;
    DallasTemperature sensors;

public:
    static const int TEMP_READ_EVENT_ID = 11; ///< ID del evento de lectura de temperatura.
    static const Event TEMP_READ_EVENT;       ///< Evento predefinido de lectura de temperatura.

    /**
     * @brief Construye un sensor de temperatura.
     * @param pin Pin digital del bus OneWire.
     * @param eventHandler Handler que recibirá los eventos (default: nullptr).
     */
    TemperatureSensor(int pin, EventHandler* eventHandler = nullptr);

    /**
     * @brief Inicializa el sensor DS18B20.
     */
    void begin();

    /**
     * @brief Lee la temperatura actual en grados Celsius.
     * @return Temperatura en °C.
     */
    float readTemp();
};

#endif // TEMPERATURE_SENSOR_H
