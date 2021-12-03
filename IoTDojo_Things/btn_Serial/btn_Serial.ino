#define BTN 4
#define LED 5

void setup() {
  Serial.begin(115200);
  pinMode(LED,OUTPUT);
  pinMode(BTN,INPUT);
}

void loop() {
  if(digitalRead(BTN)==HIGH){
    Serial.print(BTN);
    Serial.println(" pin is pressed!");
    digitalWrite(LED,HIGH);
    delay(1000);
    digitalWrite(LED,LOW);
  }
}
