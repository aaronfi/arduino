#include "config.h"           // defines NUM_LED; used here and also in our custom library, CustomCRGBArray

#include <avr/pgmspace.h>     // Needed to store stuff in Flash using PROGMEM
#include "FastLED.h"          // Fastled library to control the LEDs
#include "CustomCRGBArray.h"

#define DATA_PIN 2            // must match the data outpin number you're using on your Arduino board

// Returns a fraction of a color; abstracts the fadeToBlack out to this function in case we
// want to improve the color math or do color correction all in one location at a later date.
CRGB ColorFraction(CRGB colorIn, float fraction)
{
  fraction = min(1.0f, fraction);
  return CRGB(colorIn).fadeToBlackBy(255 * (1.0f - fraction));
}

void DrawPixels(CustomCRGBArray<NUM_LEDS> *leds, float fPos, float count, CRGB color)
{
  // Calculate how much the first pixel will hold
  float availFirstPixel = 1.0f - (fPos - (long)(fPos));
  float amtFirstPixel = min(availFirstPixel, count);
  float remaining = min(count, 64-fPos);
  int iPos = fPos;

  // Blend (add) in the color of the first partial pixel

  if (remaining > 0.0f)
  {
    (*leds)[iPos++] += ColorFraction(color, amtFirstPixel);
    remaining -= amtFirstPixel;
  }

  // Now draw any full pixels in the middle

  while (remaining > 1.0f)
  {
    (*leds)[iPos++] += color;
    remaining--;
  }

  // Draw tail pixel, up to a single full pixel

  if (remaining > 0.0f)
  {
    (*leds)[iPos] += ColorFraction(color, remaining);
  }
}

void DrawMarqueeComparison(CustomCRGBArray<NUM_LEDS> *leds)
{
  static float scroll = 0.0f;
  scroll += 0.1f;
  if (scroll > 28.0)
    scroll -= 28.0;

  // for (float i = scroll; i < 13; i+= 9)
  // {
    DrawPixels(leds, scroll, 3, CRGB::Blue);
    DrawPixels(leds, 28-(int)scroll, 3, CRGB::Yellow);
  // }
}

CustomCRGBArray<NUM_LEDS> leds;

void setup() { 
  // Serial.begin(115200);  // DEBUGGERY
  FastLED.addLeds<NEOPIXEL,DATA_PIN>(leds, NUM_LEDS);  // initializes the FastLED library
  FastLED.setBrightness(35);
  FastLED.clear();
}


void loop() {
  FastLED.clear();
  DrawMarqueeComparison(&leds);
  FastLED.show();
  delay(10);
}
