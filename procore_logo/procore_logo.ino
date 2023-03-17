#include "config.h"           // defines NUM_LED; used here and also in our custom library, CustomCRGBArray

#include <avr/pgmspace.h>     // Needed to store stuff in Flash using PROGMEM
#include "FastLED.h"          // Fastled library to control the LEDs
#include "CustomCRGBArray.h"
#include "pixelset.h"         // TODO do I still need this?

#include "images_arlo.h"
#include "images_procore_logo.h"
#include "images_qbert.h"

#define DATA_PIN 2            // must match the data outpin number you're using on your Arduino board

// FractionalColor
//
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
            (*this->leds)[led_index] = 0xFF7694;
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
uint8_t gHue = 0; // rotating "base color" used by many of the patterns

Picture *arlo;
Picture *procoreLogo;

void setup() { 
  // Serial.begin(115200);  // DEBUGGERY
  FastLED.addLeds<NEOPIXEL,DATA_PIN>(leds, NUM_LEDS);  // initializes the FastLED library
  FastLED.setBrightness(25);
  FastLED.clear();

  // arlo = new Picture(&leds, Arlo, 12, 5, 3.0, 0.0, 0.1, 0.1, true);
  // procoreLogo = new Picture(&leds, ProcoreLogo, 16, 16, 15, 15, 1, 1);

  // size(820, 820);
  // background(0);
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
  // fill_rainbow( leds, 1024, gHue, 7);

  // // a colored dot sweeping back and forth, with fading trails
  // fadeToBlackBy( leds, NUM_LEDS, 20);
  // int pos = beatsin16( 13, 0, NUM_LEDS-1 );
  // leds[pos] += CHSV( gHue, 255, 192);

  // // send the 'leds' array out to the actual LED strip
  // FastLED.show();  
  // // insert a delay to keep the framerate modest
  // //FastLED.delay(1000/120); 

  // // do some periodic updates
  // EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow

  // // procoreLogo->clearImage();
  // arlo->clearImage();
  // // procoreLogo->drawImage();
  // arlo->drawImage();
  // // FastLED.clear();
  // // DrawMarqueeComparison(&leds);
  // // FastLED.show();
  // delay(10);

  time = millis();  // lets have the animation speed independent from the framerate
  time = time * 0.1 ;  // global speed setting, could also be time*3 or anything
  c = time / 2200;  // speeds of the linear scrollings relative to global speed
  d = time / 3130;
 
  for (int x = 0; x < num_x; x++) {
    for (int y = 0; y < num_y; y++) {
      float a  = (num_x-1)/2 + (6 * sin( 1.3 * c * 10  ) ); 
      float aa = (num_y-1)/2 + (6 * cos( 1.3 * c * 10  ) ); 
      float red_size=8;      
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
  //FastLED.delay(10);
}
