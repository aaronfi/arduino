#include "config.h"           // defines NUM_LED; used here and also in our custom library, CustomCRGBArray

#include <avr/pgmspace.h>     // Needed to store stuff in Flash using PROGMEM
#include "FastLED.h"          // Fastled library to control the LEDs
#include "CustomCRGBArray.h"

#include "images_arlo.h"
#include "images_procore_logo.h"

#define DATA_PIN 2            // must match the data outpin number you're using on your Arduino board
#define HOT_PINK 0xff0033

class Picture {
  public:

  Picture(CustomCRGBArray<NUM_LEDS> *leds, const long *image, int width, int height, float x, float y, float x_offset, float y_offset, bool isBitmask = false) {
    this->leds = leds;
    this->image = image;
    this->width = width;
    this->height = height;
    this->x = x;
    this->y = x;
    this->x_offset = x_offset;
    this->y_offset = y_offset;
    this->isBitmask = isBitmask;
  }

  void drawImage() {
    this->updateImageLocation();

    // render the image
    for (float j=this->y; j<this->y+this->height; j++) {
      for (float i=this->x; i<this->x+this->width; i++) {
        int image_index = (i-x) + (j-y) * this->width;
        int led_index = i + j * 32;
        if (this->isBitmask) {
          if (pgm_read_dword(&(this->image[image_index]))) {
            (*this->leds)[led_index] = HOT_PINK;
          }
        } else {
          (*this->leds)[led_index] = pgm_read_dword(&(this->image[image_index]));
        }
      }
    }
  }

  void clearImage() {
    for (int i=this->x; i<this->x+this->width; i++) {
      for (int j=this->y; j<this->y+this->height; j++) {
        int led_index = i + j * 32;
        (*this->leds)[led_index] = CRGB::Black;
      }
    }
  }

  void updateImageLocation() { // "tick" forward the image's drifting motion across the grid
    if (this->x + this->x_offset > 32 - this->width || this->x + this->x_offset < 0) {
      if (this->x + this->x_offset < 0) {
        this->x++;
      }
      this->x_offset = -this->x_offset;
    }
    this->x += this->x_offset;

    if (this->y + this->y_offset > 32 - this->height || this->y + this->y_offset < 0) {
      this->y_offset = -this->y_offset;
    }
    if (this->y + this->y_offset < 0) {
      this->y++;
    }  
    this->y += this->y_offset;
  }

  private:
    CustomCRGBArray<NUM_LEDS> *leds;
    int width;
    int height;
    float x;
    float y;
    float x_offset;
    float y_offset;
    bool isBitmask;
    long *image;
};

CustomCRGBArray<NUM_LEDS> leds;

Picture *arlo;
Picture *procoreLogo;

void setup() { 
  // Serial.begin(115200);  // DEBUGGERY
  FastLED.addLeds<NEOPIXEL,DATA_PIN>(leds, NUM_LEDS);  // initializes the FastLED library
  FastLED.setBrightness(35);
  FastLED.clear();

  arlo = new Picture(&leds, Arlo, 12, 5, 3, 0, 1, 1, true);
  procoreLogo = new Picture(&leds, ProcoreLogo, 16, 16, 15, 15, 1, 1);
}

void loop() {
  procoreLogo->clearImage();
  arlo->clearImage();

  procoreLogo->drawImage();
  arlo->drawImage();

  FastLED.show();
  FastLED.delay(10);
}
