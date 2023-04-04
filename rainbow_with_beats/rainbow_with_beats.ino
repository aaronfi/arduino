#include "config.h"           // defines NUM_LED; used here and also in our custom library, CustomCRGBArray
#include "FastLED.h"          // Fastled library to control the LEDs
#include "CustomCRGBArray.h"

#define DATA_PIN 2

CustomCRGBArray<NUM_LEDS> leds;

void setup() {
  FastLED.addLeds<NEOPIXEL,DATA_PIN>(leds, NUM_LEDS);  // initializes the FastLED library
  FastLED.setBrightness(15);
  FastLED.clear(true);
}

void loop () {
    uint16_t beatA = beatsin16(30, 0, 255);
    uint16_t beatB = beatsin16(20, 0, 255);
    fill_rainbow(leds, NUM_LEDS, (beatA+beatB)/2, 2);
    FastLED.show();
}
