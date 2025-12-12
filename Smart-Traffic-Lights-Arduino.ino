#include "wifi_server.h"
#include "sensor_pir.h"
#include "settings.h"
#include "parser.h"
#include "algo_dynamic.h"
#include "send_http_response.h"

const int pirPinLeft = 2;     // Left pin connected to PIR sensor
const int pirPinRight = 7;     // Right pin connected to PIR sensor
int statusLeft = 0;
int statusRight = 0;
unsigned long currentMillis;


void setup() {
    Serial.begin(9600);

    initWiFiServer();   // Initialize WiFi and web server
    initPIRSensor(pirPinLeft);    // Initialize PIR motion sensor
    initPIRSensor(pirPinRight);    // Initialize PIR motion sensor
}

void loop() {
    currentMillis = millis();

    statusLeft = readPIR(pirPinLeft);          // Read PIR sensor state
    statusRight = readPIR(pirPinRight);         // Read PIR sensor state
    start_dynamic(statusLeft, statusRight);
    handleWebServer();  // Handle HTTP clients and POST requests
}
