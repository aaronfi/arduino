#ifndef CUSTOMCRGBARRAY_H
#define CUSTOMCRGBARRAY_H

#include <FastLED.h>

template<int SIZE>
class CustomCRGBArray : public CRGBArray<SIZE> {
public:  
    /// access a single element in this set, just like an array operator
    CRGB & operator[](int n) const;
};

#endif