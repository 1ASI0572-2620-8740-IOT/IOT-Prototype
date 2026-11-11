#include "ServoActuator.h"
#include <Arduino.h>

const Command ServoActuator::OPEN_COMMAND = Command(OPEN_COMMAND_ID);
const Command ServoActuator::CLOSE_COMMAND = Command(CLOSE_COMMAND_ID);

ServoActuator::ServoActuator(int pin, CommandHandler* commandHandler)
    : Actuator(pin, commandHandler), angle(0) {}

void ServoActuator::begin() {
    servo.attach(pin);
    servo.write(0);
    angle = 0;
}

void ServoActuator::handle(Command command) {
    if (command == OPEN_COMMAND) {
        servo.write(0);
        angle = 0;
    } else if (command == CLOSE_COMMAND) {
        servo.write(90);
        angle = 90;
    }
    Actuator::handle(command); // Propaga al handler si está configurado
}

int ServoActuator::getAngle() const {
    return angle;
}
