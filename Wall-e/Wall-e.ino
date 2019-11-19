#include <LedControl.h>
#include <Servo.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "binary.h"

LedControl lc = LedControl(6,5,4,1); //DIN,CLK,CS
RF24 radio(7,8);
const byte address[6] = "00001";
Servo left;
Servo right;
int joy[3]={90,90,1};
unsigned long last=0;
unsigned long blinkInterval=4000;

byte up_face_norm = B00100100;
byte up_face_blink[4] = {B00000000, B00100100, B01011010, B00000000};
byte low_face_norm[4] = {B00000000, B01000010, B01000010, B00111100};
byte low_face_laugh[4] = {B00000000, B01111110, B01111110, B00111100};
byte heart_hollow[8] = {B00000000, B01100110, B10011001, B10000001, B10000001, B01000010, B00100100, B00011000};
byte heart_full[8] = {B00000000, B01100110, B11111111, B11111111, B11111111, B01111110, B00111100, B00011000};

void setup() {  
  left.attach(10);
  right.attach(3);
  Serial.begin(9600);
  lc.shutdown(0, false);
  lc.setIntensity(0,2);
  lc.clearDisplay(0);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  unsigned long current = millis();
  if((unsigned long)(current - last) >= blinkInterval){
    lc.clearDisplay(0);
    lowerFace();
    for(int j = 0; j<4; j++){
      lc.setColumn(0,j,up_face_blink[j]);
      delay(10);
    }
    last = millis();
  }else{
    for(int i = 0; i<4; i++){
      lc.setColumn(0, i, up_face_norm);
    }
  lowerFace();
  }
  if(radio.available()){
    radio.read(&joy, sizeof(joy));
    int x = map(joy[0]-joy[1],-512,512,0,180);
    int y = map(joy[0]+joy[1],512,1536,180,0);
    right.write(x<=100&&x>=85?90:x);
    left.write(y<=100&&y>=85?90:y);
  }
}
void heart(){
  if(joy[2]==0){
    for(int j = 0; j<8; j++){
      lc.setColumn(0,j,heart_full[j]); 
    }
    tone(2,1000); 
  }else if(joy[2]==1){
    for(int i = 0; i<8; i++){
      lc.setColumn(0,i,heart_hollow[i]);
    }
    noTone(2);
  }  
}
void lowerFace(){
  if(joy[2]==0){
    for(int i = 0; i<4; i++){
      lc.setColumn(0, 7-i, low_face_laugh[3-i]);
    }
    tone(2,100);
  }else if(joy[2]==1){
    for(int j = 0; j<4; j++){
      lc.setColumn(0, 7-j, low_face_norm[3-j]);
    }
    noTone(2);
  }
}
