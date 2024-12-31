#ifndef MY_SERVER_H
#define MY_SERVER_H


#include "page.h"
#include "requestParser.h"
#include "internet.h"

WiFiServer server(80);

bool serverRunning = false;

void stopServer() {
  server.end();
  serverRunning = false;
  Serial.println("[Server] Stopped");
}


void startServer() {
  server.begin();
  serverRunning = true;
  Serial.println("[Server] Started");
}


void serverLoop() {
  if(!serverRunning) {
    if(internetConnected) {
      startServer();
    }
  }
  else {
    if(!internetConnected) {
      stopServer();
    }
    // WiFiClient client = server.available();
    WiFiClient client = server.accept();
    if (client) {
      String request = "";
      while (client.connected()) {
        if (client.available()) {
          char c = client.read();
          request += c;

          // End of HTTP headers
          if (request.endsWith("\r\n\r\n")) {
            break;
          }
        }
      }
      HttpRequest parsedRequest = parseRequest(request);
      // printParsedRequest(parsedRequest);
      // Serial.println();
      if(parsedRequest.method == "GET") {
        if(parsedRequest.path == "/index") {
          // Serial.println("HTML");
          sendHTML(client);
        }
        else {
          Serial.println("Path not correct");
        }
      }
      else {
        Serial.println("Request not correct");
      }
      client.stop();
    }
  }
}

#endif // MY_SERVER_H