#include <SoftwareSerial.h>

SoftwareSerial BT(2,3);

const int trigPin = 8;
const int echoPin = A0;
const int Klaxon = 11;

void setup() {
  Serial.begin(9600);
  BT.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(Klaxon, OUTPUT);
  
 }

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long timeDistance = pulseIn(echoPin, HIGH);
  if(timeDistance==0) return;
  long distance = (timeDistance/2) / 29.1;

  if(distance <= 10){
    tone(Klaxon, 262);
    delay(500);
    noTone(Klaxon);
    return;
  }
  
  if(Serial.available())
    BT.write(Serial.read());

  if(BT.available()){
    char dir = BT.read();

    if(dir == 'c'){
      tone(Klaxon, 262);
      delay(500);
      noTone(Klaxon);
    }
  }
    Serial.write(BT.read());
}
