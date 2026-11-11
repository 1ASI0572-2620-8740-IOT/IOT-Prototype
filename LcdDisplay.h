#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

#include "Actuator.h"
#include <LiquidCrystal_I2C.h>

/**
 * @brief Actuador de visualización basado en LCD I2C 16x2.
 *        Muestra los valores de pH y temperatura.
 */
class LcdDisplay : public Actuator {
private:
    LiquidCrystal_I2C lcd;
    float ph;
    float temp;

public:
    static const int UPDATE_DISPLAY_COMMAND_ID = 20; ///< ID del comando de actualización.
    static const Command UPDATE_DISPLAY_COMMAND;     ///< Comando predefinido de actualización.

    /**
     * @brief Construye un display LCD I2C.
     * @param addr Dirección I2C del LCD.
     * @param cols Número de columnas.
     * @param rows Número de filas.
     * @param commandHandler Handler que recibirá los comandos propagados (default: nullptr).
     */
    LcdDisplay(uint8_t addr, uint8_t cols, uint8_t rows, CommandHandler* commandHandler = nullptr);

    /**
     * @brief Inicializa el LCD (init + backlight).
     */
    void begin();

    /**
     * @brief Actualiza el valor de pH a mostrar.
     */
    void setPh(float value);

    /**
     * @brief Actualiza el valor de temperatura a mostrar.
     */
    void setTemp(float value);

    /**
     * @brief Maneja comandos del display.
     */
    void handle(Command command) override;
};

#endif // LCD_DISPLAY_H
