#include<WiFi.h>

const char* ssid     = "ssid";
const char* password = "password";

const char* HOST = "俺のPCのIP";
const String POST_URL = "/postData";
const String GET_URL = "/getData";

void Post(String mes) {
  WiFiClient client;
  String cont = "{\"msg\": \"" + mes + "\"}";
  if (!client.connect(HOST, 80)) {
    Serial.println("Not connect");
    return;
  }
  client.println("POST " + POST_URL + " HTTP/1.1");
  client.println("Content-Length: " + String(cont.length()));
  client.println("Content-Type: application/json");
  client.println("Host: " + String(HOST));
  client.println("Accept: */*");
  client.println("Connection: close");
  client.println();
  client.println(cont);
  Serial.println(cont);
  delay(100);
}

String Get() {
  WiFiClient client;
  if (!client.connect(HOST, 80)) {
    Serial.println("Not connect");
    return "err";
  }
  client.println("GET " + GET_URL + " HTTP/1.1");
  client.println("Host: " + String(HOST));
  client.println("Accept: */*");
  client.println("Connection: close");
  client.println();

  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println("Time out");
      return "err";
    }
  }
  String cont = "";
  while (client.available()) {
    char c = client.read();
    cont = cont +c;
  }  
  Serial.println(cont);
  return cont;
}

void setup() {
  WiFi.begin(ssid, password);
  Serial.begin(115200);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
}

void loop() {
  if(Serial.available()>0){
    int c=Serial.read();
    if(c=='P'){
      while(!Serial.available());
      String mes=Serial.readStringUntil('\n');
      mes.replace("\r","");
      Post(mes);
    }else if(c=='G'){
      Get();
    }
  }
}
