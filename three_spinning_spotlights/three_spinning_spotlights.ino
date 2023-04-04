#include "config.h"           // defines NUM_LED; used here and also in our custom library, CustomCRGBArray

#include <avr/pgmspace.h>     // Needed to store stuff in Flash using PROGMEM
#include "FastLED.h"          // Fastled library to control the LEDs
#include "CustomCRGBArray.h"

#define DATA_PIN 2            // must match the data outpin number you're using on your Arduino board

CustomCRGBArray<NUM_LEDS> leds;

void setup() { 
  // Serial.begin(115200);  // DEBUGGERY
  FastLED.addLeds<NEOPIXEL,DATA_PIN>(leds, NUM_LEDS);  // initializes the FastLED library
  FastLED.setBrightness(35);
  FastLED.clear();
}

float scale  = 7;  // the zoom factor for the layers
float scale2 = 5;
float c, d, time;
float shift1, shift2;
float r, g, b;
 
float num_x = 32;
float num_y = 32;
int rct = 20;
int sz = 15;

void loop() {
  // // send the 'leds' array out to the actual LED strip
  // FastLED.show();  
  // // insert a delay to keep the framerate modest
  // //FastLED.delay(1000/120); 

  time = millis();  // lets have the animation speed independent from the framerate
  time = time * 1000000 ;  // global speed setting, could also be time*3 or anything
  c = time / 2200;  // speeds of the linear scrollings relative to global speed
  // d = time / 3130;
 
  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {
      float a  = (num_x-1)/2 + (6 * sin( 1.3 * c * 10  ) ); 
      float aa = (num_y-1)/2 + (6 * cos( 1.3 * c * 10  ) ); 
      float red_size=30;      
      float scale_x = 1;
      float scale_y = 1;
      float aaa = 255-((red_size)*sqrt(((a-x)*(a-x))+((aa-y)*(aa-y))));
 
      float f = (num_x-1)/2 +(8*sin(c*8.2));
      float ff = (num_y-1)/2 +(8*sin(c*9.58));
      float green_size = ((1+sin(c*5)) * 15 ) + 15;      //size of the spot
      float fff = (255-((green_size)*sqrt(((f-x)*(f-x))+((ff-y)*(ff-y)))));
 
      float h = (num_x-1)/2 +(8*sin(c*3.43));
      float hh = (num_y-1)/2 +(8*sin(c*1.8));
      float blue_size = ((1+sin(c*6)) * 15 ) + 15;      //size of the spot
      float hhh = (255-((blue_size)*sqrt(((h-x)*(h-x))+((hh-y)*(hh-y)))));
 
      
      int led_index = x + y * 32;
      leds[led_index] = CRGB::CRGB(aaa, fff, hhh);
      // rect( 15+x*rct, 15+y*rct, sz, sz, 3);
    }
  }
  FastLED.show();
  // FastLED.delay(10);
}
