#include "wifi_server.h"
#include "form_data_parser.h"
#include "send_http_response.h"
#include <Arduino.h>

#define SECRET_SSID "trafficSensor"
#define SECRET_PASS "supersecret"

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;
int status = WL_IDLE_STATUS;       // Current WiFi status
WiFiServer server(80);             // Web server on port 80

// Initialize WiFi and start server
void initWiFiAP() {
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
  WiFiClient client = server.available();   // listen for incoming clients

  if (!client) {                            // if you no client, return
    return;
  }

  Serial.println("New client");           // print a message out the serial port
  String currentLine = "";                // make a String to hold incoming data from the client
  bool nextLinePOSTBody = false;          // Reset nextLinePOSTBody variable
  bool isPost = false;                    // Reset isPost variable
  while (client.connected()) {            // loop while the client's connected
    delayMicroseconds(10);                // This is required for the Arduino Nano RP2040 Connect - otherwise it will loop so fast that SPI will never be served.
    if (!client.available()) {            // if there's no client, break out of the while loop
      break;
    }
    char c = client.read();             // read a byte
    Serial.write(c);                    // print it out to the serial monitor
    if (c != '\r' && c != '\n') {       // if you have any character other than a carriage return or new line character,
      currentLine += c;                 // add it to the end of the currentLine
      continue;
    }

    if (c == '\r') {
      continue;
    }

    // The following code only executes when c == '\n'(newline character):

    // Check if it was a post request
    if (currentLine.startsWith("POST /")) {
      isPost = true;
    }

    if (currentLine.length() == 0 && !isPost) {
      // if the current line is blank, there are now two newline characters in a row.
      // If it's not a POST request, that means it's the end of the client HTTP request, so send a response:
      sendHTTPResponse(client);
      break;
    }

    if (isPost && currentLine.length() == 0) {
      // If we reach this point in the code, that means that we are at the end of the POST headers
      // The next line will be the POST payload.
      nextLinePOSTBody = true;
      continue;
    }

    // clear currentLine since there's a new line
    currentLine = "";
  }

  if (nextLinePOSTBody) {
    parseForm(currentLine);
    sendHTTPResponse(client);
  }

  // close the connection:
  client.stop();
  Serial.println("Client disconnected");
}

// Print WiFi AP info
void printWiFiStatus() {
    Serial.print("SSID: "); Serial.println(WiFi.SSID());
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: "); Serial.println(ip);
    Serial.print("Open a browser to http://"); Serial.println(ip);
}
