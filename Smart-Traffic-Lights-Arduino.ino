/*
  WiFi Web Server LED Blink
 
  A simple web server that lets you blink an LED via the web.
  This sketch will create a new access point (with no password).
  It will then launch a new server and print out the IP address
  to the Serial Monitor. From there, you can open that address in a web browser
  to turn on and off the LED on pin 13.
 
  If the IP address of your board is yourAddress:
    http://yourAddress/H turns the LED on
    http://yourAddress/L turns it off
 
  created 25 Nov 2012
  by Tom Igoe
  adapted to WiFi AP by Adafruit
 
  Find the full UNO R4 WiFi Network documentation here:
  https://docs.arduino.cc/tutorials/uno-r4-wifi/wifi-examples#access-point
 */
 
#include "WiFiS3.h"
#define SECRET_SSID "trafficSensor"
#define SECRET_PASS "supersecret"
 
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;        // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;                 // your network key index number (needed only for WEP)

int led = 13;
int pir = 2;
int pirStat = 0;
int status = WL_IDLE_STATUS;
WiFiServer server(80);

float distance = 100; // meters
float maxSpeed = 30; // km/h
bool isPost = false;
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
 
void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Access Point Web Server");
 
  pinMode(led, OUTPUT);      // set the LED pin mode
  pinMode(pir, INPUT);
 
  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }
 
  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }
 
  // by default the local IP address will be 192.168.4.1
  // you can override it with the following:
  WiFi.config(IPAddress(192,48,56,2));
 
  // print the network name (SSID);
  Serial.print("Creating access point named: ");
  Serial.println(ssid);
 
  // Create open network. Change this line if you want to create an WEP network:
  status = WiFi.beginAP(ssid, pass);
  if (status != WL_AP_LISTENING) {
    Serial.println("Creating access point failed");
    // don't continue
    while (true);
  }
 
  // wait 10 seconds for connection:
  delay(10000);
 
  // start the web server on port 80
  server.begin();
 
  // you're connected now, so print out the status
  printWiFiStatus();
}
 
 
void loop() {
  pirStat = digitalRead(pir);
  
  // compare the previous status to the current status
  if (status != WiFi.status()) {
    // it has changed update the variable
    status = WiFi.status();
 
    if (status == WL_AP_CONNECTED) {
      // a device has connected to the AP
      Serial.println("Device connected to AP");
    } else {
      // a device has disconnected from the AP, and we are back in listening mode
      Serial.println("Device disconnected from AP");
    }
  }
 
  WiFiClient client = server.available();   // listen for incoming clients
 
  if (!client) {                             // if you no client, return
    return;
  }

  Serial.println("new client");           // print a message out the serial port
  String currentLine = "";                // make a String to hold incoming data from the client
  while (client.connected()) {            // loop while the client's connected
    delayMicroseconds(10);                // This is required for the Arduino Nano RP2040 Connect - otherwise it will loop so fast that SPI will never be served.
    if (!client.available()) {            // if there's no client, continue
      continue;
    }

    char c = client.read();             // read a byte, then
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
      Serial.write("<Was a post request>\n");
      isPost = true;
    }

    if (currentLine.length() == 0 && !isPost) {
      // if the current line is blank, you got two newline characters in a row.
      // If it's not a POST request, that's the end of the client HTTP request, so send a response:
      Serial.write("Two \\n characters in a row\n");
      // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
      // and a content-type so the client knows what's coming, then a blank line:
      client.println("HTTP/1.1 200 OK");
      client.println("Content-type:text/html");
      client.println();

      client.print(htmlResponse);
      // The HTTP response ends with another blank line:
      client.println();
      // break out of the while loop:
      break;
    }

    
    if (isPost && currentLine.length() == 0) {
      // If we reach this point in the code, that means that we are at the end of the POST headers
      // The following line wil lbe the POST payload.
      // Setting isPost to false here will allows the next block of code to be run
      isPost = false;
      continue;
    }

    if (!isPost) {
      parseForm(currentLine);
      Serial.println(distance + '\n');
      Serial.println(maxSpeed + '\n');
      client.println(htmlResponse);
      break; // Break out of the while loop
    }

    // clear currentLine since there's a new line
    currentLine = ""; 
  }
  // close the connection:
  client.stop();
  Serial.println("client disconnected");
}
 
void printWiFiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
 
  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
 
  // print where to go in a browser:
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}

void parseForm(String data) {
    // Example: "distance=100&speed=30"
    Serial.println("parsing");
    int dIndex = data.indexOf("distance=");
    if (dIndex != -1) {
        int amp = data.indexOf('&', dIndex);
        String d = data.substring(dIndex + 9, amp);
        distance = d.toFloat();
        Serial.print("Distance set to: ");
        Serial.println(distance);
    }

    int sIndex = data.indexOf("speed=");
    if (sIndex != -1) {
        int amp = data.indexOf('&', sIndex);
        String s = data.substring(sIndex + 6);
        maxSpeed = s.toFloat();
        Serial.print("Speed set to: ");
        Serial.println(maxSpeed);
    }
}