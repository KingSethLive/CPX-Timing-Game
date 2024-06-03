//Kenneth Robertson
//5/29/2024
//Key Game
/*
Description/Rules:
There are 2 green pixles lit up, and 1 red pixel spinning around the circle. If you push either button and stop the red pixle inbetween the green pixels, you pass on to the next level.
Levels will progressivly get faster. If you pass a level the lights will flash green, then continue to the next level. If you lose then the lights will flash red and a tone will play, then start over at the beginning.
There will also be two modes for the user, using the switch. If the switch is in the first position. Then the sound will be on, else the sound will be off.
*/

/*
Inputs:
Button pin 4 and 5 have a 0-1 integer range, they will be used to stop the red pixel in its tracks by triggering an ISR.
Switch has a 0-1 integer range, it will be used to toggle the sound by triggering an ISR.
*/

#include <Adafruit_CircuitPlayground.h>
int lightPos;
int speed = 1000;
int buttonPinR = 5;
int buttonPinL = 4;
int sliderPin = 7;
int randomPos;
bool volatile buttonFlag = false;
bool sliderVal;
bool volatile sliderFlag = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  CircuitPlayground.begin();
  while(!Serial);
  attachInterrupt(digitalPinToInterrupt(buttonPinR), buttonInt, FALLING);
  attachInterrupt(digitalPinToInterrupt(buttonPinL), buttonInt, FALLING);
  attachInterrupt(digitalPinToInterrupt(sliderPin), sliderInt, CHANGE);
  randomSeed(analogRead(0));
  sliderVal = CircuitPlayground.slideSwitch();
}

void loop() {
  if(sliderFlag){
    delay(10);
    sliderVal = CircuitPlayground.slideSwitch();
    sliderFlag=false;
    // Serial.println(sliderVal);
  }
  randomPos = random(10);
  //Main game loop
  while(!buttonFlag){
    CircuitPlayground.setPixelColor(randomPos, 0, 255, 0);
    CircuitPlayground.setPixelColor((randomPos+2)%10, 0, 255, 0);
    for(int i = 0; i < 10; i++){
      lightPos = i;
      if(i != randomPos && i != (randomPos+2)%10){
        CircuitPlayground.setPixelColor(i, 255, 0, 0);
        delay(speed);
        CircuitPlayground.setPixelColor(i, 0,0,0);
      }
      if(buttonFlag){
        break;
      }
      
    }
  }
  CircuitPlayground.clearPixels();
  buttonFlag = false;
  //if you win
  if(lightPos == (randomPos+1)%10){
    speed -= 100;
    for(int i = 0; i < 10; i++){
      CircuitPlayground.setPixelColor(i, 0, 255, 0);
    }
    delay(1000);
    CircuitPlayground.clearPixels();
    delay(500);
    for(int i = 0; i < 10; i++){
      CircuitPlayground.setPixelColor(i, 0, 255, 0);
    }
    delay(1000);
    CircuitPlayground.clearPixels();
  }
  //If you lose
  else{
    if(sliderVal){
      CircuitPlayground.playTone(60, 100);
      //Serial.println(sliderVal);
    }
    speed = 1000;
    for(int i = 0; i < 10; i++){
      CircuitPlayground.setPixelColor(i, 255, 0, 0);
    }
    delay(1000);
    CircuitPlayground.clearPixels();
    delay(500);
    for(int i = 0; i < 10; i++){
      CircuitPlayground.setPixelColor(i, 255, 0, 0);
    }
    delay(1000);
    CircuitPlayground.clearPixels();
  }
}
  
void buttonInt(){
  buttonFlag = !buttonFlag;
}
void sliderInt(){
  sliderFlag = true;
}
