/**
 * @file sketch.ino
 * @brief Dispositivo de telemetría (pH + temperatura) usando Modest IoT Nano-framework.
 */
#include "ModestIoT.h"
#include "TelemetryDevice.h"
#include "CloudConfig.h"
#include <WiFi.h>

TelemetryDevice device;

void setup() {
    Serial.begin(115200);

    // Conexion WiFi
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD, 6);
    Serial.print("Conectando a WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println();
    Serial.print("WiFi conectado, IP: ");
    Serial.println(WiFi.localIP());
    Serial.println("Iniciando dispositivo...");

    device.begin();

    // Mensaje de bienvenida
    delay(2000);
    device.getLcd().handle(LcdDisplay::UPDATE_DISPLAY_COMMAND);
}

void loop() {
    device.triggerPhReadEvent();
    device.triggerTempReadEvent();

    delay(1000); // Actualiza lecturas cada segundo
}
