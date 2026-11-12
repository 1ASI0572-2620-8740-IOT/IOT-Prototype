#ifndef CLOUD_CONFIG_H
#define CLOUD_CONFIG_H

// ---------- WiFi ----------
#define WIFI_SSID     "Wokwi-GUEST"
#define WIFI_PASSWORD ""

// ---------- Backend ----------
#define CLOUD_BASE_URL "https://hg-8740-edge-wokwi.onrender.com"

// Identidad SIMULATION: reemplaza con los valores reales del dispositivo
#define CLOUD_DEVICE_ID  "SIMULATION_DEVICE_ID"
#define CLOUD_CREDENTIAL "SIMULATION_CREDENTIAL"

// ---------- Endpoints ----------
#define CLOUD_HEALTH_ENDPOINT "/health"
#define CLOUD_DEVICE_AUTH_ENDPOINT "/edge/v1/device-auth/session"
#define CLOUD_TELEMETRY_ENDPOINT "/edge/v1/telemetry"

// ---------- CA root ----------
// No se usa: TLS en modo insecure (setInsecure), como en el ejemplo basico de Wokwi.

#endif // CLOUD_CONFIG_H
