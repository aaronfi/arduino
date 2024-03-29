/*
 * Meteor Shower posted by Chemdoc77
 * Based on the outstanding MeteorShower sketch by Jon Burroughs as seen in Adam bluebottleyellowboxyellyfish’s clock
 * which Chemdoc77 slightly modified.
 */

// TODO 2023.04.03 currently the loop doesn't render anything...loopCount

#include "config.h"           // defines NUM_LED; used here and also in our custom library, CustomCRGBArray

#include "CustomCRGBArray.h"
#include <FastLED.h>

#define LED_PIN 2 

#define BRIGHTNESS 10
CustomCRGBArray<NUM_LEDS> leds;

byte ledsX[NUM_LEDS][3];
boolean RAINBOWs = false;
boolean RANDOMpick = false;
uint8_t hue;
uint16_t timeframe;
byte idex = 0;
byte colorTIP = 0;
byte meteorLENGTH;
byte loopCount = 1;    //low number loop counter

void setup() {
  Serial.begin(115200);  // DEBUGGERY

  delay(1000); // sanity delay
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness( BRIGHTNESS );
  FastLED.setMaxPowerInVoltsAndMilliamps(5,1500);
  set_max_power_indicator_LED(13);
  fill_solid(leds, NUM_LEDS, CRGB::Red);
  FastLED.show();
}

void loop() {
  meteorShower();
}

void meteorShower() {
  //hue master
  hue++;  
 
  //populate the leds[] with stored ledsX[] array data
  for(byte i = 0; i < NUM_LEDS; i++ ) {
    ledsX[i][0] = leds[i].r;
    ledsX[i][1] = leds[i].g;
    ledsX[i][2] = leds[i].b;
  }
  //clear the previous counter clockwise position
  byte iCCW;
 
  //we are keeping track of elapsed time
  timeframe++;    //fx timer
 
  //meteorLENGTH fx is only shown for this time frame
  if((timeframe >= 1) && (timeframe <= 280)) { meteorLENGTH = 29; }
  if((timeframe > 280) && (timeframe <= 500)) { meteorLENGTH = 45; }
 
  //RAINBOWs fx add rainbow tails during this time frame only
  if((timeframe > 0) && (timeframe <= 280)) { RAINBOWs = true; }
  else{ RAINBOWs = false; }  
  //keep our RAINBOWs within a specific range of hue
  if(RAINBOWs == true){ hue = hue - 20; if(hue <= 0){  hue = 1; } }
 
  //RANDOMpick fx is only enabled during this timeframe
  if((timeframe > 600) && (timeframe <= 790)) { RANDOMpick = true; }
  else{ RANDOMpick = false; }
 
  //pick a random spot in the meteor switch case statement below
  if (RANDOMpick == true){ idex = random8(46); }
  else{
    //increment the meteor display frame
    idex++;
    //make sure we don't drift into space
    if (idex > meteorLENGTH) { idex = 0; } }  
 
  //meteorLENGTH is randomized during this timeframe only
  if((timeframe > 790) && (timeframe <= 1090)) { meteorLENGTH = random8(7, 38); }
 
  //during this point in the animation timeframe
  if(timeframe == 1180) {
    //reset the timeframe
    timeframe = 0;
    //increment the loop counter
    loopCount++;
  }
 
  //during this part of the loopCount, all meteors have a white colored tip
  if(loopCount == 1) { colorTIP = 0; }
  if(loopCount == 2) { colorTIP = 1; }
  if(loopCount == 3) { colorTIP = random8(11); }
  //end of the desired fx, reset the variable for the next time around
  if(loopCount == 4) {
    colorTIP = 0;
    loopCount = 0;
  }
 
  //there are two switch case statements nestled into one another
  //we always want to control the color of the meteor tip
  //the other controls the actual meteor animation in 45 frames/case statements
  switch (idex) {
  case 0:
    switch (colorTIP){
    case 0:
      leds[0] = CHSV(hue, 255, 255);
      break;
    case 1:
      leds[0] = CRGB(100,100,100);
      break;
    case 2:
      leds[0] = CRGB::Yellow;
      break;
    case 3:
      leds[0] = CRGB::Violet;
      break;
    case 4:
      leds[0] = CRGB::Green;
      break;
    case 5:
      leds[0] = CRGB::Purple;
      break;
    case 6:
      leds[0] = CRGB::Orange;
      break;
    case 7:
      leds[0] = CRGB::Cyan;
      break;
    case 8:
      leds[0] = CRGB::GreenYellow;
      break;
    case 9:
      leds[0] = CRGB::Magenta;
      break;
    case 10:
      leds[0] = CRGB::SkyBlue;
    }
    break;
  case 1:
    leds[0] = CHSV((hue - 20), 255, 210);
    break;
  case 2:
    leds[0] = CHSV((hue - 22), 255, 180);
    break;
  case 3:
    leds[0] = CHSV((hue - 23), 255, 150);
    break;
  case 4:
    leds[0] = CHSV((hue - 24), 255, 110);
    break;
  case 5:
    leds[0] = CHSV((hue - 25), 255, 90);
    break;
  case 6:
    leds[0] = CHSV((hue - 26), 160, 60);
    break;
  case 7:
    leds[0] = CHSV((hue - 27), 140, 40);
    break;
  case 8:
    leds[0] = CHSV((hue - 28), 120, 20);
    break;
  case 9:
    leds[0] = CHSV((hue - 29), 100, 20);
    break;
  case 10:
    leds[0] = CRGB::Black;
    break;
  case 11:
    leds[0] = CRGB::Black;
    break;
  case 12:
    leds[0] = CRGB::Black;
    break;
  case 13:
    leds[0] = CRGB::Black;
    break;
  case 14:
    leds[0] = CRGB::Black;
    break;
  case 15:
    leds[0] = CRGB::Black;
    break;
  case 16:
    leds[0] = CRGB::Black;
    break;
  case 17:
    leds[0] = CRGB::Black;
    break;
  case 18:
    leds[0] = CRGB::Black;
    break;
  case 19:
    leds[0] = CRGB::Black;
    break;
  case 20:
    leds[0] = CRGB::Black;
    break;
  case 21:
    leds[0] = CRGB::Black;
    break;
  case 22:
    leds[0] = CRGB::Black;
    break;
  case 23:
    leds[0] = CRGB::Black;
    break;
  case 24:
    leds[0] = CRGB::Black;
    break;
  case 25:
    leds[0] = CRGB::Black;
    break;
  case 26:
    leds[0] = CRGB::Black;
    break;
  case 27:
    leds[0] = CRGB::Black;
    break;
  case 28:
    leds[0] = CRGB::Black;
    break;
  case 29:
    leds[0] = CRGB::Black;
    break;
  case 30:
    leds[0] = CRGB::Black;
    break;
  case 31:
    leds[0] = CRGB::Black;
    break;
  case 32:
    leds[0] = CRGB::Black;
    break;
  case 33:
    leds[0] = CRGB::Black;
    break;
  case 34:
    leds[0] = CRGB::Black;
    break;
  case 35:
    leds[0] = CRGB::Black;
    break;
  case 36:
    leds[0] = CRGB::Black;
    break;
  case 37:
    leds[0] = CRGB::Black;
    break;
  case 38:
    leds[0] = CRGB::Black;
    break;
  case 39:
    leds[0] = CRGB::Black;
    break;
  case 40:
    leds[0] = CRGB::Black;
    break;
  case 41:
    leds[0] = CRGB::Black;
    break;
  case 42:
    leds[0] = CRGB::Black;
    break;
  case 43:
    leds[0] = CRGB::Black;
    break;
  case 44:
    leds[0] = CRGB::Black;
    break;
  case 45:
    leds[0] = CRGB::Black;
    break;
  }
  //copy the LED Array
  for(byte i = 1; i < NUM_LEDS; i++ ) {
    iCCW = adjacent_ccw(i);
    leds[i].r = ledsX[iCCW][0];
    leds[i].g = ledsX[iCCW][1];
    leds[i].b = ledsX[iCCW][2];
  }
  //show the blinky
  FastLED.show();  
  //control the animation speed/frame rate
  delay(30);
}
 
//find the adjacent counter clockwise postion of the led
//funkboxing code snippet
byte adjacent_ccw(byte i) {
  byte r;
  if (i > 0) { r = i - 1; }
  else { r = NUM_LEDS - 1; }
  return r;  
}
