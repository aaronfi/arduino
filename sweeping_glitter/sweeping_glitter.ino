#include "config.h"           // defines NUM_LED; used here and also in our custom library, CustomCRGBArray

#include <avr/pgmspace.h>     // Needed to store stuff in Flash using PROGMEM
#include "FastLED.h"          // Fastled library to control the LEDs
#include "CustomCRGBArray.h"

#define DATA_PIN 2            // must match the data outpin number you're using on your Arduino board

CustomCRGBArray<NUM_LEDS> leds;
uint8_t gHue = 0; // rotating "base color" used by many of the patterns

void setup() { 
  // Serial.begin(115200);  // DEBUGGERY
  FastLED.addLeds<NEOPIXEL,DATA_PIN>(leds, NUM_LEDS);  // initializes the FastLED library
  FastLED.setBrightness(35);
  FastLED.clear();
}

void loop() {
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16( 13, 0, NUM_LEDS-1 );
  leds[pos] += CHSV( gHue, 255, 192);

  EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow
  
  FastLED.show();
  FastLED.delay(10);
}
