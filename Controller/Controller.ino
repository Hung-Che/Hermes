#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
const byte addresses[6] = "00001";

void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(2, INPUT_PULLUP); 
  radio.begin();
  radio.openWritingPipe(addresses); 
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}
void loop() {
  int x = (analogRead(A0)<=100&&analogRead(A0)>=85)?90:analogRead(A0);
  int y = (analogRead(A1)<=100&&analogRead(A1)>=85)?90:analogRead(A1);
  int joy[3] = {x,y,digitalRead(2)};
  radio.write(&joy, sizeof(joy));
    Serial.print("X: ");
    Serial.print(x);
    Serial.print(" | Y: ");
    Serial.print(y);
    Serial.print(" | Button: ");
    Serial.print(digitalRead(2));
    Serial.print(" |");
    Serial.println(map(joy[0]-joy[1],-512,512,0,180));
}
