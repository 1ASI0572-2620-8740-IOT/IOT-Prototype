#include "CloudClient.h"
#include "CloudConfig.h"
#include <WiFi.h>

bool CloudClient::begin() {
    // En Wokwi/simulacion no es necesario verificar el certificado.
    // Equivalente al ejemplo HTTPClient basico (http.begin(url) sin CA).
    secureClient.setInsecure();
    Serial.println("[Cloud] TLS en modo insecure (sin verificacion de certificado)");
    return true;
}

bool CloudClient::get(const char* path) {
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("[Cloud] WiFi no conectado");
        return false;
    }

    HTTPClient http;
    String url = String(CLOUD_BASE_URL) + path;
    http.begin(secureClient, url);
    http.useHTTP10(true);
    http.setTimeout(15000);
    http.addHeader("X-Device-Id", CLOUD_DEVICE_ID);
    http.addHeader("X-Credential", CLOUD_CREDENTIAL);

    int code = http.GET();
    Serial.printf("[Cloud] GET %s -> HTTP %d\n", path, code);
    if (code > 0) {
        Serial.println(http.getString());
    } else {
        Serial.printf("[Cloud] Error: %s\n", http.errorToString(code).c_str());
    }
    http.end();
    return code >= 200 && code < 300;
}

bool CloudClient::health() {
    return get(CLOUD_HEALTH_ENDPOINT);
}
