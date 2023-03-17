#include <avr/pgmspace.h> 
#include "images_arlo.h"

// TODO does this really need to be a long?
// It's just a bitmask.

const long Arlo[] PROGMEM = 
{ // 12x5
  1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0,
  1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0,
  1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1,
  1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1,
  1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1,
};
