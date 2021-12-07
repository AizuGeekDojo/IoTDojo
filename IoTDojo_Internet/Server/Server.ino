#include <WiFi.h>
#include <WebServer.h>

const char* ssid     = "ssid";
const char* password = "password";

const int LED=5;
bool flg=HIGH;

WebServer server(80);

void mainPage() {
  server.send(200, "text/html","<!DOCTYPE html>\n<html lang='en'>\n<head>\n<meta charset='UTF-8'>\n<meta http-equiv='X-UA-Compatible' content='IE=edge'>\n<meta name='viewport' content='width=device-width, initial-scale=1.0'>\n<title>IoT Dojo</title>\n<link href='https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css' rel='stylesheet'\nintegrity='sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC' crossorigin='anonymous'>\n</head>\n<body>\n<!-- header -->\n<header>\n<div class='navbar navbar-dark bg-dark shadow-sm'>\n<div class='container'>\n<div class='navbar-brand d-flex align-items-center'>\n<strong>IoT Dojo</strong>\n</div>\n</div>\n</div>\n</header>\n<main class='container'>\n<section>\n<div class='text-center'>\n<p class='led-state'>\n現在の状態: 点灯\n</p>\n</div>\n</section>\n<section>\n<h3>Lチカボタン</h3>\n<br>\n<div class='row'>\n<div class='text-center'>\n<button class='btn btn-primary' onclick='on()'>点灯</button>\n<button class='btn btn-danger' onclick='off()'>消灯</button>\n</div>\n</div>\n</div>\n</section>\n</main>\n</body>\n<script src='https://unpkg.com/axios/dist/axios.min.js'></script>\n</html>\n<style>\nmain {\npadding-top: 50px;\n}\nh3 {\npadding: 1rem 2rem;\nborder-left: 5px solid #000;\nbackground: #f4f4f4;\n}\nbutton {\nwidth: 120px;\nheight: 80px;\nmargin-bottom: 10px;\nmargin-right: 20px;\nmargin-left: 20px;\nfont-size: 1.5rem !important;\n}\n.led-state {\nfont-size: 1.8rem;\n}\n</style>\n<script>\nconst LEDStatePath = '/state';\nconst changeLEDPath = '/change';\nconst post = (path, body) => {\nconst request = new XMLHttpRequest();\nrequest.open('POST', path, false);\nrequest.setRequestHeader('Content-Type', 'text/plain');\nrequest.send(body);\nif (request.status === 200) {\nalert('リクエストに成功しました');\nreturn JSON.parse(request.responseText);\n} else {\nalert('リクエストに失敗しました');\nreturn 0;\n}\n}\nconst get = (path) => {\nconst request = new XMLHttpRequest();\nrequest.open('GET', path, false);\nrequest.send(null);\nif (request.status === 200) {\nreturn JSON.parse(request.responseText);\n} else {\nalert('リクエストに失敗しました');\nreturn 0;\n}\n}\nconst on = () => {\npost(changeLEDPath, 'on');\n}\nconst off = () => {\npost(changeLEDPath, 'off');\n}\nconst updateLEDState = (state) => {\nconst ledState = document.querySelector('.led-state');\nledState.innerText = `現在の状態: ${state}`;\n}\nconst LEDState = () => {\nconst res = get(LEDStatePath);\nif (res == 0) {\nalert('ページをリロードしてください');\nreturn;\n}\nconst state = res.state;\nupdateLEDState(state);\n}\nsetInterval(() => LEDState(), 5000);\n</script>");
}

void sendState() {
  if(server.method()!=HTTP_GET){
    server.send(404,"text/plain","ng");
  }
  server.send(200, "application/json", "{\"state\":\""+String(flg?"ON":"OFF")+"\"}");
}
void getChange(){
  String mes;
  if(server.method()!=HTTP_POST){
    Serial.println("cant this method");
    server.send(404,"text/plain","ng");
  }
  mes=server.arg("plain");
  if(mes=="on"){
    flg=HIGH;
    Serial.println("ON!");
  }else if(mes=="off"){
    flg=LOW;
    Serial.println("OFF!");
  }else{
    Serial.print(mes);
    Serial.println("is not found");
    server.send(404,"text/plain","ng");
  }
  digitalWrite(LED,flg);
  server.send(200, "text/plain", "ok");
}

void setup(void) {
  pinMode(LED,OUTPUT);
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  server.on("/", mainPage);
  server.on("/state",sendState);
  server.on("/change",getChange);
  server.begin();
}

void loop(void) {
  server.handleClient();
}
