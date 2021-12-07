#include <WiFi.h>
#include <WebServer.h>

const char* ssid     = "ssid";
const char* password = "password";

const int LED=5;
bool flg=HIGH;

WebServer server(80);

void mainPage() {
  server.send(200, "text/html","<!DOCTYPE html>\n<html lang='en'>\n<head>\n<meta charset='UTF-8'>\n<meta http-equiv='X-UA-Compatible' content='IE=edge'>\n<meta name='viewport' content='width=device-width, initial-scale=1.0'>\n<title>IoT Dojo</title>\n<link href='https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css' rel='stylesheet'\nintegrity='sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC' crossorigin='anonymous'>\n</head>\n<body>\n<!-- header -->\n<header>\n<div class='navbar navbar-dark bg-dark shadow-sm'>\n<div class='container'>\n<div class='navbar-brand d-flex align-items-center'>\n<strong>IoT Dojo</strong>\n</div>\n</div>\n</div>\n</header>\n<main class='container'>\n<section>\n<div class='text-center'>\n<p class='led-state'>\n現在の状態: 点灯\n</p>\n</div>\n</section>\n<section>\n<h3>Lチカボタン</h3>\n<br>\n<div class='row'>\n<div class='text-center'>\n<button class='btn btn-primary' onclick='on()'>点灯</button>\n<button class='btn btn-danger' onclick='off()'>消灯</button>\n</div>\n</div>\n</div>\n</section>\n</main>\n</body>\n<script src='https://unpkg.com/axios/dist/axios.min.js'></script>\n</html>\n<style>\nmain {\npadding-top: 50px;\n}\nh3 {\npadding: 1rem 2rem;\nborder-left: 5px solid #000;\nbackground: #f4f4f4;\n}\nbutton {\nwidth: 120px;\nheight: 80px;\nmargin-bottom: 10px;\nmargin-right: 20px;\nmargin-left: 20px;\nfont-size: 1.5rem !important;\n}\n.led-state {\nfont-size: 1.8rem;\n}\n</style>\n<script>\nconst LEDStatePath = '/state';\nconst changeLEDPath = '/change';\nconst post = (path, body) => {\naxios.post(path, body,{\nheaders: {'Content-Type':'text/plain'}\n})\n.then(function (response) {\nconsole.log(response);\nalert(`リクエストに成功しました`);\n})\n.catch(function (error) {\nconsole.log(error);\nalert(`リクエストに失敗しました`);\n});\n}\nconst get = async (path) => {\ntry {\nreturn await axios.get(path);\n} catch (error) {\nconsole.log(error);\nalert(`リクエストに失敗しました`);\nreturn 0;\n}\n}\nconst on = () => {\npost(changeLEDPath,'on');\n}\nconst off = () => {\npost(changeLEDPath,'off');\n}\nconst updateLEDState = (state) => {\nconst ledState = document.querySelector('.led-state');\nledState.innerText = `現在の状態: ${state}`;\n}\nconst sleep = (ms) => {\nreturn new Promise(resolve => setTimeout(resolve, ms));\n}\nconst LEDState = async () => {\nwhile (1) {\nconst res = await get(LEDStatePath);\nif (res == 0) {\nalert('ページをリロードしてください');\nreturn;\n}\nconst state = res.data.state;\nupdateLEDState(state);\nawait sleep(5000);\n}\n}\nLEDState();\n</script>");
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
