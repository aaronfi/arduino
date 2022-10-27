#include <avr/pgmspace.h>  // Needed to store stuff in Flash using PROGMEM
#include "FastLED.h"       // Fastled library to control the LEDs

#define NUM_LEDS 1024      // 32x32 board 
#define DATA_PIN 2         // must match the data outpin number you're using on your Arduino board

CRGBArray<NUM_LEDS> leds;

const long Qbert[] PROGMEM = 
{
  // Qbert
  0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
  0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
  0x000000, 0x000000, 0x000000, 0x000000, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
  0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff6600, 0xff6600, 0xff6600, 0x000000, 0x000000, 
  0x000000, 0xff0033, 0xff0033, 0xff6600, 0xff0033, 0xffffcc, 0xffffcc, 0xff0033, 0xffffcc, 0xffffcc, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
  0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xff0033, 0x000000, 0x000000, 0xff0033, 0xff6600, 0xff6600, 0xff0033, 0xff0033, 
  0xff0033, 0xff0033, 0xff0033, 0xff6600, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff6600, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
  0x000000, 0x000000, 0x000000, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff0033, 0xff0033, 0xff6600, 0xff6600, 0xff6600, 0xff0033, 0xff0033,  
  0xff0033, 0xff0033, 0xff0033, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0x000000, 0x000000, 
  0x000000, 0xff6600, 0xff6600, 0xff6600, 0xff0033, 0xff0033, 0xff0033, 0xff6600, 0xff0033, 0xff6600, 0xff0033, 0xff6600, 0xff0033, 0xff6600, 0xff0033, 0xff0033, 
  0x000000, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff6600, 0xff0033, 0xff0033, 0x000000, 0xff0033, 0xff0033, 0x000033, 0x000033, 0xff6600, 0x000000, 
  0x000000, 0xff0033, 0x000033, 0x000033, 0xff0033, 0x000000, 0x000000, 0x000000, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0x000000, 0x000000, 
  0x000000, 0x000000, 0x000000, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0x000000, 0x000000, 0x000000, 0x000000, 0xff0033, 0xff0033, 0x000000, 0x000000, 
  0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xff0033, 0x000000, 0x000000, 0xff0033, 0x000000, 0x000000, 0x000000, 0x000000,
  0x000000, 0x000000, 0xff6600, 0xff6600, 0xff6600, 0x000000, 0x000000, 0xff0033, 0xff6600, 0xff6600, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
  0x000000, 0x000000, 0x000000, 0x000000, 0xff6600, 0xff6600, 0xff0033, 0x000000, 0x000000, 0xff6600, 0xff6600, 0xff6600, 0xff0033, 0x000000, 0x000000, 0x000000,
};

const long ProcoreLogo[] PROGMEM =  // 16x16 image 
{
  // Procore logo
  0xf4f5f6, 0xf4f5f6, 0x8d8e8e, 0x7c7e7f, 0x7c7e7f, 0x7c7e7f, 0x7c7e7f, 0x7c7e7f, 0x7c7e7f, 0x7c7e7f, 0x7c7e7f, 0x7c7e7f, 0x7c7e7f, 0x8d8e8e, 0xf4f5f6, 0xf4f5f6, 
  0xf4f5f6, 0x595d61, 0x161d26, 0x111821, 0x111821, 0x111821, 0x111821, 0x111821, 0x111821, 0x111821, 0x111821, 0x111821, 0x111821, 0x161d26, 0x595d61, 0xf4f5f6, 
  0x66686b, 0x121922, 0x111821, 0x111821, 0x111821, 0x111821, 0x111821, 0x111821, 0x111821, 0x111821, 0x111821, 0x111821, 0x111821, 0x111821, 0x121922, 0x66686b, 
  0x191f28, 0x111821, 0x111821, 0x111821, 0x111821, 0x41454c, 0x4f5357, 0x4f5357, 0x4f5357, 0x4f5357, 0x41454c, 0x111821, 0x111821, 0x111821, 0x111821, 0x191f28, 
  0x111821, 0x111821, 0x111821, 0x111821, 0x252a32, 0x949494, 0xf4f5f6, 0xf4f5f6, 0xf4f5f6, 0xf4f5f6, 0x949494, 0x252a32, 0x111821, 0x111821, 0x111821, 0x111821, 
  0x111821, 0x111821, 0x111821, 0x121922, 0x78797b, 0xf4f5f6, 0xac897d, 0xc07c67, 0xc07c67, 0xac897d, 0xf4f5f6, 0x78797b, 0x121922, 0x111821, 0x111821, 0x111821, 
  0x8c8d8d, 0x8c8d8d, 0x8c8d8d, 0x8c8d8d, 0xf4f5f6, 0x9a9492, 0xf4561a, 0xfc5100, 0xfc5100, 0xf4561a, 0x9a9492, 0xf4f5f6, 0x383d44, 0x111821, 0x111821, 0x111821,
  0x111821, 0x111821, 0x111821, 0x383d44, 0xf4f5f6, 0x9a9492, 0xf4561a, 0xfc5100, 0xfc5100, 0xf4561a, 0x9a9492, 0xf4f5f6, 0x8c8d8d, 0x8c8d8d, 0x8c8d8d, 0x8c8d8d, 
  0xf4f5f6, 0xf4f5f6, 0xf4f5f6, 0xf4f5f6, 0xf4f5f6, 0xcf7356, 0xfc5100, 0xfc5100, 0xfc5100, 0xfc5100, 0xcf7356, 0xf4f5f6, 0x89898a, 0x151b24, 0x111821, 0x111821, 
  0x111821, 0x111821, 0x151b24, 0x89898a, 0xf4f5f6, 0xcf7356, 0xfc5100, 0xfc5100, 0xfc5100, 0xfc5100, 0xcf7356, 0xf4f5f6, 0xf4f5f6, 0xf4f5f6, 0xf4f5f6, 0xf4f5f6,
  0x111821, 0x111821, 0x111821, 0x121922, 0x78797b, 0xf4f5f6, 0xac897d, 0xc07c67, 0xc07c67, 0xac897d, 0xf4f5f6, 0x78797b, 0x121922, 0x111821, 0x111821, 0x111821,
  0x111821, 0x111821, 0x111821, 0x111821, 0x252a32, 0x949494, 0xf4f5f6, 0xf4f5f6, 0xf4f5f6, 0xf4f5f6, 0x949494, 0x252a32, 0x111821, 0x111821, 0x111821, 0x111821, 
  0x191f28, 0x111821, 0x111821, 0x111821, 0x111821, 0x41454c, 0x4f5357, 0x4f5357, 0x4f5357, 0x4f5357, 0x41454c, 0x111821, 0x111821, 0x111821, 0x111821, 0x191f28, 
  0x66686b, 0x121922, 0x111821, 0x111821, 0x111821, 0x111821, 0x111821, 0x111821, 0x111821, 0x111821, 0x111821, 0x111821, 0x111821, 0x111821, 0x121922, 0x66686b, 
  0xf4f5f6, 0x595d61, 0x161d26, 0x111821, 0x111821, 0x111821, 0x111821, 0x111821, 0x111821, 0x111821, 0x111821, 0x111821, 0x111821, 0x161d26, 0x595d61, 0xf4f5f6, 
  0xf4f5f6, 0xf4f5f6, 0x8d8e8e, 0x7c7e7f, 0x7c7e7f, 0x7c7e7f, 0x7c7e7f, 0x7c7e7f, 0x7c7e7f, 0x7c7e7f, 0x7c7e7f, 0x7c7e7f, 0x7c7e7f, 0x8d8e8e, 0xf4f5f6, 0xf4f5f6, 

  // Qbert
  0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
  0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
  0x000000, 0x000000, 0x000000, 0x000000, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
  0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff6600, 0xff6600, 0xff6600, 0x000000, 0x000000, 
  0x000000, 0xff0033, 0xff0033, 0xff6600, 0xff0033, 0xffffcc, 0xffffcc, 0xff0033, 0xffffcc, 0xffffcc, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
  0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xff0033, 0x000000, 0x000000, 0xff0033, 0xff6600, 0xff6600, 0xff0033, 0xff0033, 
  0xff0033, 0xff0033, 0xff0033, 0xff6600, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff6600, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
  0x000000, 0x000000, 0x000000, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff0033, 0xff0033, 0xff6600, 0xff6600, 0xff6600, 0xff0033, 0xff0033,  
  0xff0033, 0xff0033, 0xff0033, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0x000000, 0x000000, 
  0x000000, 0xff6600, 0xff6600, 0xff6600, 0xff0033, 0xff0033, 0xff0033, 0xff6600, 0xff0033, 0xff6600, 0xff0033, 0xff6600, 0xff0033, 0xff6600, 0xff0033, 0xff0033, 
  0x000000, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff6600, 0xff0033, 0xff0033, 0x000000, 0xff0033, 0xff0033, 0x000033, 0x000033, 0xff6600, 0x000000, 
  0x000000, 0xff0033, 0x000033, 0x000033, 0xff0033, 0x000000, 0x000000, 0x000000, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0x000000, 0x000000, 
  0x000000, 0x000000, 0x000000, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0x000000, 0x000000, 0x000000, 0x000000, 0xff0033, 0xff0033, 0x000000, 0x000000, 
  0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xff0033, 0x000000, 0x000000, 0xff0033, 0x000000, 0x000000, 0x000000, 0x000000,
  0x000000, 0x000000, 0xff6600, 0xff6600, 0xff6600, 0x000000, 0x000000, 0xff0033, 0xff6600, 0xff6600, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
  0x000000, 0x000000, 0x000000, 0x000000, 0xff6600, 0xff6600, 0xff0033, 0x000000, 0x000000, 0xff6600, 0xff6600, 0xff6600, 0xff0033, 0x000000, 0x000000, 0x000000,

  0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
  0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
  0x000000, 0x000000, 0x000000, 0x000000, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
  0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff6600, 0xff6600, 0xff6600, 0x000000, 0x000000, 
  0x000000, 0xff0033, 0xff0033, 0xff6600, 0xff0033, 0xffffcc, 0xffffcc, 0xff0033, 0xffffcc, 0xffffcc, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
  0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xff0033, 0x000000, 0x000000, 0xff0033, 0xff6600, 0xff6600, 0xff0033, 0xff0033, 
  0xff0033, 0xff0033, 0xff0033, 0xff6600, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff6600, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
  0x000000, 0x000000, 0x000000, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff0033, 0xff0033, 0xff6600, 0xff6600, 0xff6600, 0xff0033, 0xff0033,  
  0xff0033, 0xff0033, 0xff0033, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0x000000, 0x000000, 
  0x000000, 0xff6600, 0xff6600, 0xff6600, 0xff0033, 0xff0033, 0xff0033, 0xff6600, 0xff0033, 0xff6600, 0xff0033, 0xff6600, 0xff0033, 0xff6600, 0xff0033, 0xff0033, 
  0x000000, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff6600, 0xff0033, 0xff0033, 0x000000, 0xff0033, 0xff0033, 0x000033, 0x000033, 0xff6600, 0x000000, 
  0x000000, 0xff0033, 0x000033, 0x000033, 0xff0033, 0x000000, 0x000000, 0x000000, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0x000000, 0x000000, 
  0x000000, 0x000000, 0x000000, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0x000000, 0x000000, 0x000000, 0x000000, 0xff0033, 0xff0033, 0x000000, 0x000000, 
  0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xff0033, 0x000000, 0x000000, 0xff0033, 0x000000, 0x000000, 0x000000, 0x000000,
  0x000000, 0x000000, 0xff6600, 0xff6600, 0xff6600, 0x000000, 0x000000, 0xff0033, 0xff6600, 0xff6600, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
  0x000000, 0x000000, 0x000000, 0x000000, 0xff6600, 0xff6600, 0xff0033, 0x000000, 0x000000, 0xff6600, 0xff6600, 0xff6600, 0xff0033, 0x000000, 0x000000, 0x000000,

  0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
  0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
  0x000000, 0x000000, 0xFFFFFF, 0x000000, 0x000000, 0x000000, 0xFFFFFF, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
  0x000000, 0x000000, 0xFFFFFF, 0x000000, 0x000000, 0x000000, 0xFFFFFF, 0x000000, 0xff0033, 0xff0033, 0xff0033, 0xff6600, 0xff6600, 0xff6600, 0x000000, 0x000000, 
  0x000000, 0x000000, 0xFFFFFF, 0x000000, 0x000000, 0x000000, 0xFFFFFF, 0x000000, 0xffffcc, 0xffffcc, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
  0x000000, 0x000000, 0xFFFFFF, 0x000000, 0x000000, 0x000000, 0xFFFFFF, 0x000000, 0xff0033, 0x000000, 0x000000, 0xff0033, 0xff6600, 0xff6600, 0xff0033, 0xff0033, 
  0xff0033, 0x000000, 0xFFFFFF, 0x000000, 0x000000, 0x000000, 0xFFFFFF, 0x000000, 0xff0033, 0xff0033, 0xff6600, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
  0x000000, 0x000000, 0xFFFFFF, 0x000000, 0x000000, 0x000000, 0xFFFFFF, 0x000000, 0xff6600, 0xff0033, 0xff0033, 0xff6600, 0xff6600, 0xff6600, 0xff0033, 0xff0033,  
  0xff0033, 0x000000, 0xFFFFFF, 0x000000, 0x000000, 0x000000, 0xFFFFFF, 0x000000, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0x000000, 0x000000, 
  0x000000, 0x000000, 0xFFFFFF, 0x000000, 0x000000, 0x000000, 0xFFFFFF, 0x000000, 0xff0033, 0xff6600, 0xff0033, 0xff6600, 0xff0033, 0xff6600, 0xff0033, 0xff0033, 
  0x000000, 0x000000, 0xFFFFFF, 0x000000, 0x000000, 0x000000, 0xFFFFFF, 0x000000, 0xff0033, 0x000000, 0xff0033, 0xff0033, 0x000033, 0x000033, 0xff6600, 0x000000, 
  0x000000, 0x000000, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0x000000, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0x000000, 0x000000, 
  0x000000, 0x000000, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xff0033, 0xff0033, 0x000000, 0x000000, 
  0x000000, 0x000000, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0x000000, 0xff0033, 0x000000, 0x000000, 0xff0033, 0x000000, 0x000000, 0x000000, 0x000000,
  0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xff6600, 0xff6600, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 
  0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xff6600, 0xff6600, 0xff6600, 0xff0033, 0x000000, 0x000000, 0x000000,

  // // mostly pink block
  // 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 
  // 0x000000, 0x000000, 0x000000, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 
  // 0x000000, 0x000000, 0x000000, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 
  // 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 
  // 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 
  // 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 
  // 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 
  // 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 
  // 0xff0033, 0xff0033, 0xff0033, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0x000000, 0x000000, 
  // 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 
  // 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 
  // 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 
  // 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 
  // 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 
  // 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 
  // 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033, 0xff0033,

  // // mostly blue block
  // 0x000000, 0x000000, 0x000000, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 
  // 0x000000, 0x000000, 0x000000, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 
  // 0x000000, 0x000000, 0x000000, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 
  // 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 
  // 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 
  // 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 
  // 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 
  // 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 
  // 0x0000FF, 0x0000FF, 0x0000FF, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0xff6600, 0x000000, 0x000000, 
  // 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 
  // 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 
  // 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 
  // 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 
  // 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 
  // 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 
  // 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF,
};

void renderImage(long image[]) {
  FastLED.clear();
  // quadrants 1 and 2 (northeast and southeast)
  for(int i = 0; i < 512; i++) {
    leds[i] = pgm_read_dword(&(image[i]));  // read array from Flash
  }

  // quadrant 3 (southwest)
  for(int i = 512; i <= 527; i++) {
    leds[i] = pgm_read_dword(&(image[i + 240]));
  }  
  for(int i = 528; i <= 543; i++) {
    leds[i] = pgm_read_dword(&(image[i + 208]));
  }
  for(int i = 544; i <= 559; i++) {
    leds[i] = pgm_read_dword(&(image[i + 176]));
  }  
  for(int i = 560; i <= 575; i++) {
    leds[i] = pgm_read_dword(&(image[i + 144]));
  }
  for(int i = 576; i <= 591; i++) {
    leds[i] = pgm_read_dword(&(image[i + 112]));
  }  
  for(int i = 592; i <= 607; i++) {
    leds[i] = pgm_read_dword(&(image[i + 80]));
  }  
  for(int i = 608; i <= 623; i++) {
    leds[i] = pgm_read_dword(&(image[i + 48]));
  }  
  for(int i = 624; i <= 639; i++) {
    leds[i] = pgm_read_dword(&(image[i + 16]));
  }  
  for(int i = 640; i <= 655; i++) {
    leds[i] = pgm_read_dword(&(image[i - 16]));
  }  
  for(int i = 656; i <= 671; i++) {
    leds[i] = pgm_read_dword(&(image[i - 48]));
  }  
  for(int i = 672; i <= 687; i++) {
    leds[i] = pgm_read_dword(&(image[i - 80]));
  }  
  for(int i = 688; i <= 703; i++) {
    leds[i] = pgm_read_dword(&(image[i - 112]));
  }  
  for(int i = 704; i <= 719; i++) {
    leds[i] = pgm_read_dword(&(image[i - 144]));
  }  
  for(int i = 720; i <= 735; i++) {
    leds[i] = pgm_read_dword(&(image[i - 176]));
  }  
  for(int i = 736; i <= 751; i++) {
    leds[i] = pgm_read_dword(&(image[i - 208]));
  }  
  for(int i = 752; i <= 767; i++) {
    leds[i] = pgm_read_dword(&(image[i - 240]));
  }  

  // quadrant 4 (northwest)
  for(int i = 768; i <= 783; i++) {
    leds[i] = pgm_read_dword(&(image[i + 240]));
  }  
  for(int i = 784; i <= 799; i++) {
    leds[i] = pgm_read_dword(&(image[i + 208]));
  }
  for(int i = 800; i <= 815; i++) {
    leds[i] = pgm_read_dword(&(image[i + 176]));
  }  
  for(int i = 816; i <= 831; i++) {
    leds[i] = pgm_read_dword(&(image[i + 144]));
  }
  for(int i = 832; i <= 847; i++) {
    leds[i] = pgm_read_dword(&(image[i + 112]));
  }  
  for(int i = 848; i <= 863; i++) {
    leds[i] = pgm_read_dword(&(image[i + 80]));
  }  
  for(int i = 864; i <= 879; i++) {
    leds[i] = pgm_read_dword(&(image[i + 48]));
  }  
  for(int i = 880; i <= 895; i++) {
    leds[i] = pgm_read_dword(&(image[i + 16]));
  }  
  for(int i = 896; i <= 911; i++) {
    leds[i] = pgm_read_dword(&(image[i - 16]));
  }  
  for(int i = 912; i <= 927; i++) {
    leds[i] = pgm_read_dword(&(image[i - 48]));
  }  
  for(int i = 928; i <= 943; i++) {
    leds[i] = pgm_read_dword(&(image[i - 80]));
  }  
  for(int i = 944; i <= 959; i++) {
    leds[i] = pgm_read_dword(&(image[i - 112]));
  }  
  for(int i = 960; i <= 975; i++) {
    leds[i] = pgm_read_dword(&(image[i - 144]));
  }  
  for(int i = 976; i <= 991; i++) {
    leds[i] = pgm_read_dword(&(image[i - 176]));
  }  
  for(int i = 992; i <= 1007; i++) {
    leds[i] = pgm_read_dword(&(image[i - 208]));
  }  
  for(int i = 1008; i <= 1023; i++) {
    leds[i] = pgm_read_dword(&(image[i - 240]));
  }

  FastLED.show();
}

void renderImage(long image[], int x, int y) {
  

}

void setup() { 
  FastLED.addLeds<NEOPIXEL,DATA_PIN>(leds, NUM_LEDS);  // initializes the FastLED library
  FastLED.setBrightness(10);
}

void loop() { 
  renderImage(ProcoreLogo);
  // renderImage(Qbert, 20, 20);
  delay(500);
}
