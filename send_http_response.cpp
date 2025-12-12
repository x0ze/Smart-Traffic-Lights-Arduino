#include "send_http_response.h"
#include "settings.h"
#include "wifi_server.h"
#include <Arduino.h>

void sendHTTPResponse(WiFiClient client) {
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
      <input type="number" step="0.1" id="distance" name="distance" value=")HTML" + String(getDistance()) + R"HTML("><br>
      <label for="speed">Max. Speed [km/h]:</label>
      <input type="number" step="0.1" id="speed" name="speed" value=")HTML" + String(getMaxSpeed()) + R"HTML("><br>
      <input type="submit" value="Submit">
      </form>
    </body>
    </html>
  )HTML";

  // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
  // and a content-type so the client knows what's coming, then a blank line:
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println();

  client.print(htmlResponse);
  // The HTTP response ends with another blank line:
  client.println();
}