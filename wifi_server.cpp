#include "wifi_server.h"
#include "parser.h"
#include "settings.h"
#include <Arduino.h>

#define SECRET_SSID "trafficSensor"
#define SECRET_PASS "supersecret"

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;
int status = WL_IDLE_STATUS;       // Current WiFi status
WiFiServer server(80);             // Web server on port 80
bool isPost = false;               // Flag for POST request

// HTML page served to clients
String htmlResponse = R"HTML(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8" />
<title>Traffic Lights</title>
</head>
<body>
<h2>Enter values</h2>
<form action="" method="post">
<label for="distance">Distance [meters]:</label>
<input type="number" id="distance" name="distance" value="100"><br>
<label for="speed">Max. Speed [km/h]:</label>
<input type="number" id="speed" name="speed" value="30"><br>
<input type="submit" value="Submit">
</form>
</body>
</html>
)HTML";

// Initialize WiFi and start server
void initWiFiServer() {
    Serial.println("Access Point Web Server");

    // Optional: set static IP
    WiFi.config(IPAddress(192,48,56,2));

    // Start Access Point
    status = WiFi.beginAP(ssid, pass);
    if(status != WL_AP_LISTENING) {
        Serial.println("Creating access point failed");
        while(true); // Stop if AP cannot start
    }

    delay(10000); // Wait for devices to connect
    server.begin(); // Start HTTP server
    printWiFiStatus();
}

// Handle HTTP clients
void handleWebServer() {
    WiFiClient client = server.available(); // Check for incoming client
    if(!client) return;

    String currentLine = "";
    while(client.connected()) {
        delayMicroseconds(10); // Prevent overloading SPI
        if(!client.available()) continue;

        char c = client.read();
        Serial.write(c);

        if(c != '\r' && c != '\n') {
            currentLine += c; // Build line of HTTP request
            continue;
        }

        if(c == '\r') continue;

        // Detect POST request
        if(currentLine.startsWith("POST /")) isPost = true;

        // Handle GET request (send HTML page)
        if(currentLine.length() == 0 && !isPost) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print(htmlResponse);
            client.println();
            break;
        }

        // End of POST headers
        if(isPost && currentLine.length() == 0) {
            isPost = false;
            continue;
        }

        // Parse form for GET request
        if(!isPost) {
            parseForm(currentLine);
            client.println(htmlResponse);
            break;
        }

        currentLine = "";
    }

    client.stop(); // Close connection
}

// Print WiFi AP info
void printWiFiStatus() {
    Serial.print("SSID: "); Serial.println(WiFi.SSID());
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: "); Serial.println(ip);
    Serial.print("Open a browser to http://"); Serial.println(ip);
}
