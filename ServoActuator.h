#ifndef SERVO_ACTUATOR_H
#define SERVO_ACTUATOR_H

#include "Actuator.h"
#include <ESP32Servo.h>

/**
 * @brief Actuador de servomotor (SG90) controlado por PWM.
 *        Se usa para cierre de emergencia de la salida de agua.
 */
class ServoActuator : public Actuator {
private:
    Servo servo;
    int angle;

public:
    static const int OPEN_COMMAND_ID = 30;   ///< Abre la salida (0°).
    static const int CLOSE_COMMAND_ID = 31;  ///< Cierra la salida (90°).
    static const Command OPEN_COMMAND;
    static const Command CLOSE_COMMAND;

    /**
     * @brief Construye el actuador de servo.
     * @param pin Pin PWM del servo.
     * @param commandHandler Handler que recibirá los comandos propagados.
     */
    ServoActuator(int pin, CommandHandler* commandHandler = nullptr);

    /**
     * @brief Adjunta el servo al pin y lo deja en posición abierta.
     */
    void begin();

    /**
     * @brief Maneja comandos de apertura/cierre.
     */
    void handle(Command command) override;

    /**
     * @brief Ángulo actual del servo.
     */
    int getAngle() const;
};

#endif // SERVO_ACTUATOR_H
