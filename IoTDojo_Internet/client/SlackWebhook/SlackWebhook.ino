#include <WiFiClientSecure.h>

const char* ssid     = "ssid";
const char* password = "password";

const char* HOST = "hooks.slack.com";
const String URL = "/services/hogehoge";

void Send(String mes) {
  WiFiClientSecure client;
  client.setInsecure();
  String cont = "{\"text\":\"" + mes + "\"}";
  if (!client.connect(HOST, 443)) {
    Serial.println("Not connect");
    return;
  }
  client.println("POST " + URL + " HTTP/1.1");
  client.println("Content-Length: " + String(cont.length()));
  client.println("Content-Type: application/json");
  client.println("Host: " + String(HOST));
  client.println("Connection: close");
  client.println();
  client.println(cont);
  Serial.println(cont);

  delay(100);
}
void setup() {
  WiFi.begin(ssid, password);
  Serial.begin(115200);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("Start");
}

void loop() {
  if (Serial.available() > 0) {
    String c = Serial.readStringUntil('\n');
    c.replace("\r", "");
    Send(c);
  }
}
