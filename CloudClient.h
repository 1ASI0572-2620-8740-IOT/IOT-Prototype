#ifndef CLOUD_CLIENT_H
#define CLOUD_CLIENT_H

#include <Arduino.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>

/**
 * @brief Cliente HTTPS para verificar el estado del backend (health check).
 */
class CloudClient {
public:
    bool begin();        ///< Configura TLS (WiFi debe estar conectado).
    bool health();       ///< GET /health al backend.

private:
    WiFiClientSecure secureClient;
    bool get(const char* path);
};

#endif // CLOUD_CLIENT_H
