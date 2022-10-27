#include <avr/pgmspace.h>  // Needed to store stuff in Flash using PROGMEM
#include "FastLED.h"       // Fastled library to control the LEDs
#include "qbert01.h"
#include "qbert02.h"

// How many leds are connected?
#define NUM_LEDS 624

// Define the Data Pin
#define DATA_PIN 2  // Connected to the data pin of the first LED strip

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() { 
  FastLED.addLeds<NEOPIXEL,DATA_PIN>(leds, NUM_LEDS);  // Init of the Fastled library
  FastLED.setBrightness(5);
}

void loop() { 
  // Put Qbert first frame
  for(int passtime = 0; passtime < 8; passtime++) { // Display it 8 times
    FastLED.clear();
    for(int i = 0; i < NUM_LEDS; i++) {
      leds[i] = pgm_read_dword(&(Qbert01[i]));  // Read array from Flash
    }

    FastLED.show();
    delay(800);

    // put Qbert second frame
    FastLED.clear();
    for(int i = 0; i < NUM_LEDS; i++) {
      leds[i] = pgm_read_dword(&(Qbert02[i]));
    }

    FastLED.show();
    delay(800);
  }
}


// // Put DigDug first frame
// for(int passtime = 0; passtime < 8; passtime++) {

// FastLED.clear();
// for(int i = 0; i < NUM_LEDS; i++) {
//     leds[i] = pgm_read_dword(&(DigDug01[i]));
//   }

// FastLED.show();
// delay(250);


// // Put DigDug second frame
// FastLED.clear();
// for(int i = 0; i < NUM_LEDS; i++) {
//     leds[i] = pgm_read_dword(&(DigDug02[i]));
//   }

// FastLED.show();
// delay(10000);

//}

//}
