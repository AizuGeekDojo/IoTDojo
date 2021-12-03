void setup() {
  // 引数はchannel,周波数,階調数(2^8=256段階)
  ledcSetup(0,12800,8);
  ledcAttachPin(5, 0);
}
int i;
void loop() {
  for(i=0;i<256;i++){
    ledcWrite(0,i);
    delay(2);
  }
  for(i=255;i>=0;i--){
    ledcWrite(0,i);
    delay(2);
  }
}
