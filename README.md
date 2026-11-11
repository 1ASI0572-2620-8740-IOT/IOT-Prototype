# TelemetryDevice (Modest IoT)

Proyecto de telemetría (pH + temperatura DS18B20) adaptado al **Modest IoT Nano-framework (C++ Edition)**.

## Archivos
- Framework (copiados): `ModestIoT.h`, `EventHandler.h`, `CommandHandler.h`, `Sensor.*`, `Actuator.*`, `Device.*`, `Led.*`
- Nuevos componentes:
  - `PhSensor` (sensor de pH por potenciómetro)
  - `TemperatureSensor` (DS18B20)
  - `LcdDisplay` (LCD I2C 16x2)
  - `TelemetryDevice` (dispositivo que orquesta lecturas, visualización y LEDs de estado)
- `sketch.ino`, `diagram.json`, `libraries.txt`

## Hardware adicional
- LED verde en GPIO 2 (rango correcto: pH 6-8, temp 20-30°C)
- LED rojo en GPIO 5 (fuera de rango)
- Servo SG90 en GPIO 18 (cierre de emergencia de la salida de agua)

## Uso
Abrir la carpeta en Arduino IDE (ESP32) o importar en Wokwi con `diagram.json` y `libraries.txt`.

## Flujo
1. `loop()` dispara `PH_READ_EVENT` y `TEMP_READ_EVENT`.
2. `TelemetryDevice::on()` lee el sensor, actualiza el LCD y envía `UPDATE_DISPLAY_COMMAND`.
3. `LcdDisplay::handle()` refresca la pantalla.
4. `TelemetryDevice::evaluateRanges()` enciende LED verde/rojo según rangos.
5. Los valores también se imprimen por Serial.

## Notas de robustez
- `PhSensor` configura su pin como `INPUT`.
- `TemperatureSensor::readTemp()` detecta el DS18B20 desconectado (`DEVICE_DISCONNECTED_C`) y lo registra por Serial; en ese caso el dispositivo queda en estado "fuera de rango" (LED rojo + servo cerrado).
- La lectura del DS18B20 es bloqueante (~750 ms); aceptable para el ciclo de 1 s, pero puede hacerse asíncrona si se requiere mayor frecuencia.

## Preparado para GitHub
Incluye `.gitignore` para artefactos de Arduino/ESP32, Wokwi y archivos de sistema.
