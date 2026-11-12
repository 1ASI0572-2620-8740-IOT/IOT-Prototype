#include "CloudClient.h"
#include "CloudConfig.h"
#include <WiFi.h>
#include <mbedtls/base64.h>
#include <ArduinoJson.h>

static String base64Encode(const String& input) {
    size_t olen = 0;
    mbedtls_base64_encode(nullptr, 0, &olen,
                          (const unsigned char*)input.c_str(), input.length());
    char* buf = (char*)malloc(olen + 1);
    if (!buf) return String();
    mbedtls_base64_encode((unsigned char*)buf, olen, &olen,
                          (const unsigned char*)input.c_str(), input.length());
    buf[olen] = '\0';
    String out(buf);
    free(buf);
    return out;
}

bool CloudClient::begin() {
    // En Wokwi/simulacion no es necesario verificar el certificado.
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

bool CloudClient::deviceAuthSession(String& outDeviceId, String& outOrgId) {
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("[Cloud] WiFi no conectado");
        return false;
    }

    String creds = String(CLOUD_DEVICE_ID) + ":" + String(CLOUD_CREDENTIAL);
    String b64 = base64Encode(creds);

    HTTPClient http;
    String url = String(CLOUD_BASE_URL) + CLOUD_DEVICE_AUTH_ENDPOINT;
    http.begin(secureClient, url);
    http.useHTTP10(true);
    http.setTimeout(15000);
    http.addHeader("Authorization", "Basic " + b64);
    http.addHeader("Accept", "application/json");

    int code = http.GET();
    Serial.printf("[Cloud] GET %s -> HTTP %d\n", CLOUD_DEVICE_AUTH_ENDPOINT, code);
    bool ok = false;
    if (code > 0) {
        String payload = http.getString();
        Serial.println(payload);
        DynamicJsonDocument doc(512);
        DeserializationError err = deserializeJson(doc, payload);
        if (!err) {
            outDeviceId = doc["deviceId"] | "";
            outOrgId = doc["organizationId"] | "";
            Serial.printf("[Cloud] deviceId=%s organizationId=%s\n",
                          outDeviceId.c_str(), outOrgId.c_str());
            ok = true;
        } else {
            Serial.printf("[Cloud] JSON parse error: %s\n", err.c_str());
        }
    } else {
        Serial.printf("[Cloud] Error: %s\n", http.errorToString(code).c_str());
    }
    http.end();
    return ok && code >= 200 && code < 300;
}

bool CloudClient::sendTelemetry(float ph, float temp, const String& measurementId, const String& measuredAt) {
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("[Cloud] WiFi no conectado");
        return false;
    }

    String creds = String(CLOUD_DEVICE_ID) + ":" + String(CLOUD_CREDENTIAL);
    String b64 = base64Encode(creds);

    String body = "{\"measurementId\":\"" + measurementId +
                  "\",\"ph\":" + String(ph, 2) +
                  ",\"temperature\":" + String(temp, 2) +
                  ",\"measuredAt\":\"" + measuredAt + "\"}";

    HTTPClient http;
    String url = String(CLOUD_BASE_URL) + CLOUD_TELEMETRY_ENDPOINT;
    http.begin(secureClient, url);
    http.useHTTP10(true);
    http.setTimeout(15000);
    http.addHeader("Authorization", "Basic " + b64);
    http.addHeader("Content-Type", "application/json");

    int code = http.POST(body);
    Serial.printf("[Cloud] POST %s -> HTTP %d\n", CLOUD_TELEMETRY_ENDPOINT, code);
    if (code > 0) {
        Serial.println(http.getString());
    } else {
        Serial.printf("[Cloud] Error: %s\n", http.errorToString(code).c_str());
    }
    http.end();
    return code >= 200 && code < 300;
}
