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
  int joy[3] = {analogRead(A0),analogRead(A1),digitalRead(2)};
  radio.write(&joy, sizeof(joy));
    Serial.print("X: ");
    Serial.print(x);
    Serial.print(" | Y: ");
    Serial.print(y);
    Serial.print(" | Button: ");
    Serial.print(digitalRead(2));
    Serial.print(" |");
    Serial.print(map(joy[0]-joy[1],-512,512,0,180));
    Serial.print(" \ ");
    Serial.println(map(joy[0]+joy[1],512,1536,180,0));
}
