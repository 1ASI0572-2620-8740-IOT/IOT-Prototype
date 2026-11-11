#include "LcdDisplay.h"
#include <Arduino.h>

const Command LcdDisplay::UPDATE_DISPLAY_COMMAND = Command(UPDATE_DISPLAY_COMMAND_ID);

LcdDisplay::LcdDisplay(uint8_t addr, uint8_t cols, uint8_t rows, CommandHandler* commandHandler)
    : Actuator(-1, commandHandler), lcd(addr, cols, rows), ph(0.0f), temp(0.0f) {}

void LcdDisplay::begin() {
    lcd.init();
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Iniciando...");
    lcd.setCursor(0, 1);
    lcd.print("Telemetria UNAD");
}

void LcdDisplay::setPh(float value) {
    ph = value;
}

void LcdDisplay::setTemp(float value) {
    temp = value;
}

void LcdDisplay::handle(Command command) {
    if (command == UPDATE_DISPLAY_COMMAND) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("pH: ");
        lcd.print(ph, 1);
        lcd.print("        ");

        lcd.setCursor(0, 1);
        lcd.print("Temp: ");
        if (temp <= -100.0f) {
            lcd.print("Err     ");
        } else {
            lcd.print(temp, 1);
            lcd.print(" C   ");
        }
    }
    Actuator::handle(command); // Propaga al handler si está configurado
}
