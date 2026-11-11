#ifndef PH_SENSOR_H
#define PH_SENSOR_H

#include "Sensor.h"

/**
 * @brief Sensor de pH basado en un potenciómetro (entrada analógica).
 *        Mapea la lectura ADC (0-4095) a un rango de pH (0.0-14.0).
 */
class PhSensor : public Sensor {
public:
    static const int PH_READ_EVENT_ID = 10; ///< ID del evento de lectura de pH.
    static const Event PH_READ_EVENT;       ///< Evento predefinido de lectura de pH.

    /**
     * @brief Construye un sensor de pH.
     * @param pin Pin analógico del potenciómetro.
     * @param eventHandler Handler que recibirá los eventos (default: nullptr).
     */
    PhSensor(int pin, EventHandler* eventHandler = nullptr);

    /**
     * @brief Lee el valor de pH actual.
     * @return pH en rango 0.0 - 14.0.
     */
    float readPh();
};

#endif // PH_SENSOR_H
