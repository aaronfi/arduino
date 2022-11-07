//
// By Serge Skorodinsky, 11/15/2019
//

#include "SSVXYMatrix.h"
#include <FastLED.h>
#include "SSVRGBGradientCalc.h"

//rectangle conversion functions
Rectangle NormalizeRectangle(Rectangle R)
{
  uint16_t p1x = min(R.P1.X, R.P2.X);
  uint16_t p1y = min(R.P1.Y, R.P2.Y);
  uint16_t p2x = max(R.P1.X, R.P2.X);
  uint16_t p2y = max(R.P1.Y, R.P2.Y);
 return Rectangle(Point(p1x,p1y), Point(p2x,p2y) );
}

RectangleWH RectangleToRectangleWH(Rectangle R)
{
  Rectangle NR = NormalizeRectangle(R);
  return RectangleWH(NR.P1, NR.P2.X-NR.P1.X, NR.P2.Y-NR.P1.Y);
}


Rectangle RectangleWHToRectangle(RectangleWH R)
{
  uint16_t p2x = R.LeftBottom.X + R.Width;
  uint16_t p2y = R.LeftBottom.Y + R.Height;
  return Rectangle(R.LeftBottom, Point(p2x, p2y) );
}


//XYMatrix Class
  /*
  History
  1) 5/17/2020: added protection to handle out of matrix bounds in basic XYMatrix.draw_2DGradient(...) method.
  */
XYMatrix::XYMatrix(CRGB* aLeds, uint16_t MatrixWidth, uint16_t MatrixHeight, bool MatrixZigzagLayout/*, bool XYSwap, bool HSwap, bool VSwap*/)
{
  _leds=aLeds;
  _MatrixWidth = MatrixWidth;
  _MatrixHeight = MatrixHeight;
  _MatrixZigzagLayout = MatrixZigzagLayout;
  //_HSwap=HSwap;
  //_VSwap=VSwap;
  //_XYSwap=XYSwap;
}

const uint16_t grid[32][32] PROGMEM = {
  { 1024,1023,1022,1021,1020,1019,1018,1017,1016,1015,1014,1013,1012,1011,1010,1009,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1, },
  { 993,994,995,996,997,998,999,1000,1001,1002,1003,1004,1005,1006,1007,1008,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32, },
  { 992,991,990,989,988,987,986,985,984,983,982,981,980,979,978,977,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33, },
  { 961,962,963,964,965,966,967,968,969,970,971,972,973,974,975,976,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64, },
  { 960,959,958,957,956,955,954,953,952,951,950,949,948,947,946,945,80,79,78,77,76,75,74,73,72,71,70,69,68,67,66,65, },
  { 929,930,931,932,933,934,935,936,937,938,939,940,941,942,943,944,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96, },
  { 928,927,926,925,924,923,922,921,920,919,918,917,916,915,914,913,112,111,110,109,108,107,106,105,104,103,102,101,100,99,98,97, },
  { 897,898,899,900,901,902,903,904,905,906,907,908,909,910,911,912,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128, },
  { 896,895,894,893,892,891,890,889,888,887,886,885,884,883,882,881,144,143,142,141,140,139,138,137,136,135,134,133,132,131,130,129, },
  { 865,866,867,868,869,870,871,872,873,874,875,876,877,878,879,880,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160, },
  { 864,863,862,861,860,859,858,857,856,855,854,853,852,851,850,849,176,175,174,173,172,171,170,169,168,167,166,165,164,163,162,161, },
  { 833,834,835,836,837,838,839,840,841,842,843,844,845,846,847,848,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,192, },
  { 832,831,830,829,828,827,826,825,824,823,822,821,820,819,818,817,208,207,206,205,204,203,202,201,200,199,198,197,196,195,194,193, },
  { 801,802,803,804,805,806,807,808,809,810,811,812,813,814,815,816,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,224, },
  { 800,799,798,797,796,795,794,793,792,791,790,789,788,787,786,785,240,239,238,237,236,235,234,233,232,231,230,229,228,227,226,225, },
  { 769,770,771,772,773,774,775,776,777,778,779,780,781,782,783,784,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255,256, },
  { 768,767,766,765,764,763,762,761,760,759,758,757,756,755,754,753,272,271,270,269,268,267,266,265,264,263,262,261,260,259,258,257, },
  { 737,738,739,740,741,742,743,744,745,746,747,748,749,750,751,752,273,274,275,276,277,278,279,280,281,282,283,284,285,286,287,288, },
  { 736,735,734,733,732,731,730,729,728,727,726,725,724,723,722,721,304,303,302,301,300,299,298,297,296,295,294,293,292,291,290,289, },
  { 705,706,707,708,709,710,711,712,713,714,715,716,717,718,719,720,305,306,307,308,309,310,311,312,313,314,315,316,317,318,319,320, },
  { 704,703,702,701,700,699,698,697,696,695,694,693,692,691,690,689,336,335,334,333,332,331,330,329,328,327,326,325,324,323,322,321, },
  { 673,674,675,676,677,678,679,680,681,682,683,684,685,686,687,688,337,338,339,340,341,342,343,344,345,346,347,348,349,350,351,352, },
  { 672,671,670,669,668,667,666,665,664,663,662,661,660,659,658,657,368,367,366,365,364,363,362,361,360,359,358,357,356,355,354,353, },
  { 641,642,643,644,645,646,647,648,649,650,651,652,653,654,655,656,369,370,371,372,373,374,375,376,377,378,379,380,381,382,383,384, },
  { 640,639,638,637,636,635,634,633,632,631,630,629,628,627,626,625,400,399,398,397,396,395,394,393,392,391,390,389,388,387,386,385, },
  { 609,610,611,612,613,614,615,616,617,618,619,620,621,622,623,624,401,402,403,404,405,406,407,408,409,410,411,412,413,414,415,416, },
  { 608,607,606,605,604,603,602,601,600,599,598,597,596,595,594,593,432,431,430,429,428,427,426,425,424,423,422,421,420,419,418,417, },
  { 577,578,579,580,581,582,583,584,585,586,587,588,589,590,591,592,433,434,435,436,437,438,439,440,441,442,443,444,445,446,447,448, },
  { 576,575,574,573,572,571,570,569,568,567,566,565,564,563,562,561,464,463,462,461,460,459,458,457,456,455,454,453,452,451,450,449, },
  { 545,546,547,548,549,550,551,552,553,554,555,556,557,558,559,560,465,466,467,468,469,470,471,472,473,474,475,476,477,478,479,480, },
  { 544,543,542,541,540,539,538,537,536,535,534,533,532,531,530,529,496,495,494,493,492,491,490,489,488,487,486,485,484,483,482,481, },
  { 513,514,515,516,517,518,519,520,521,522,523,524,525,526,527,528,497,498,499,500,501,502,503,504,505,506,507,508,509,510,511,512, },
};

//convert x,y to index. Does not care about out of bounds
uint16_t XYMatrix::XY( uint16_t x, uint16_t y) 
{
  return grid[x][y];
  // uint16_t index;

   

  // //if (_XYSwap) {uint16_t tmp=x; x=y; y=tmp;}  //ERROR: _MatrixZigzagLayout is on X axiz now, not Y!
  // //if (_HSwap) {x=_MatrixWidth-x-1;}
  // //if (_VSwap) {y=_MatrixHeight-y-1;}
  
  // if(_MatrixZigzagLayout) 
  //   {
  //   //zigzag
  //   if( y & 0x01) 
  //     {
  //     // Odd rows run backwards
  //     uint16_t reverseX = (_MatrixWidth - 1) - x;
  //     index = (y * _MatrixWidth) + reverseX;
  //     } 
  //      else 
  //       {
  //       // Even rows run forwards
  //       index = (y * _MatrixWidth) + x;
  //       }
  //   }
  // else 
  //   { 
  //   //not zigzag  
  //   index = (y * _MatrixWidth) + x; 
  //   }
  // return index;
}

uint16_t XYMatrix::XY( Point P)
{
  return XY(P.X, P.Y);
}

void XYMatrix::setPixelColor(uint16_t x, uint16_t y, CRGB color)
{
  if( x >= _MatrixWidth) return; //error
  if( y >= _MatrixHeight) return; //error
  //if( x < 0) return; //x is unsigned
  //if( y < 0) return; //y is unsigned
  _leds[ XY(x, y)] = color; 
}

void XYMatrix::setPixelColor(Point P, CRGB color)
{
  setPixelColor(P.X, P.Y, color);
}

CRGB XYMatrix::getPixelColor(uint16_t x, uint16_t y)
{
  if( x >= _MatrixWidth) return 0; //error
  if( y >= _MatrixHeight) return 0; //error
  //if( x < 0) return; //x is unsigned
  //if( y < 0) return; //y is unsigned
  return _leds[XY(x, y)];
}

CRGB XYMatrix::getPixelColor(Point P)
{
  getPixelColor(P.X, P.Y);
}

uint16_t XYMatrix::getMatrixWidth()
{return _MatrixWidth;}

uint16_t XYMatrix::getMatrixHeight()
{return _MatrixHeight;}

bool XYMatrix::isZigzagLayout()
{return _MatrixZigzagLayout;}

void XYMatrix::setZigzagLayout(bool ZigzagLayout)
{_MatrixZigzagLayout=ZigzagLayout;}

//bool XYMatrix::isHSwap() {return _HSwap;}
//void XYMatrix::setHSwap(bool HSwap) {_HSwap=HSwap;}
//bool XYMatrix::isVSwap() {return _VSwap;}
//void XYMatrix::setVSwap(bool VSwap) {_VSwap=VSwap;}
//bool XYMatrix::isXYSwap() {return _XYSwap;}
//void XYMatrix::setXYSwap(bool XYSwap) {_XYSwap=XYSwap;}

void XYMatrix::draw_line(int x1, int y1, int x2, int y2, CRGB color, boolean includeLastPoint)
{
    //https://ru.wikibooks.org/wiki/%D0%A0%D0%B5%D0%B0%D0%BB%D0%B8%D0%B7%D0%B0%D1%86%D0%B8%D0%B8_%D0%B0%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC%D0%BE%D0%B2/%D0%90%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC_%D0%91%D1%80%D0%B5%D0%B7%D0%B5%D0%BD%D1%85%D1%8D%D0%BC%D0%B0
    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    if ((deltaX == 0) && (deltaY == 0))  //added to draw point if start and end points are the same
      {
        setPixelColor(x1,y1,color); //bounds check
        return;
      }
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    //
    if (includeLastPoint) 
      {
        //_leds[ XY(x2, y2) ] = color;  //no bounds check
        setPixelColor(x2,y2,color); //bounds check
      }

    if (deltaX ==0)
      {
        //vert.line, faster
        while (y1 != y2)
          {
            setPixelColor(x1,y1,color);
            y1 += signY;
          }
        return;  
      }

    if (deltaY ==0)
      {
        //hor.line, faster
        while (x1 != x2)
          {
            setPixelColor(x1,y1,color);
            x1 += signX;
          }
        return;  
      }
    
    //ANY line, but vert and hor are done above, faster
    int error = deltaX - deltaY;
    while(x1 != x2 || y1 != y2) 
   {
        //_leds[ XY(x1, y1) ]  = color;  //no bounds check
        setPixelColor(x1,y1,color); //bounds check
        
        const int error2 = error * 2;
        //
        if(error2 > -deltaY) 
        {
            error -= deltaY;
            x1 += signX;
        }
        if(error2 < deltaX) 
        {
            error += deltaX;
            y1 += signY;
        }
    }
}

void XYMatrix::draw_line(Point P1, Point P2, CRGB color, boolean includeLastPoint)
{
  draw_line(P1.X, P1.Y, P2.X, P2.Y, color, includeLastPoint);
}

////gradient line, different name to not confuse with default parameter "includeLastPoint"
void XYMatrix::draw_line_gradient(int x1, int y1, int x2, int y2, CRGB color1, CRGB color2, boolean includeLastPoint) //gradient
{
    //https://ru.wikibooks.org/wiki/%D0%A0%D0%B5%D0%B0%D0%BB%D0%B8%D0%B7%D0%B0%D1%86%D0%B8%D0%B8_%D0%B0%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC%D0%BE%D0%B2/%D0%90%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC_%D0%91%D1%80%D0%B5%D0%B7%D0%B5%D0%BD%D1%85%D1%8D%D0%BC%D0%B0
    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    if ((deltaX == 0) && (deltaY == 0))  //added to draw point if start and end points are the same
      {
        setPixelColor(x1,y1,color1); //bounds check
        return;
      }
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    //
    if (includeLastPoint) 
      {
        //_leds[ XY(x2, y2) ] = color;  //no bounds check
        setPixelColor(x2,y2,color2); //bounds check
      }

    if (deltaX ==0)
      {
        //vert.line, faster
        RGBGradientCalculator GC (color1,  color2,  y1, y2);
        while (y1 != y2)
          {
            setPixelColor(x1,y1, GC.GetRGBGradientColor(y1) );
            y1 += signY;
          }
        return;  
      }

    if (deltaY ==0)
      {
        //hor.line, faster
        RGBGradientCalculator GC (color1,  color2,  x1, x2);
        while (x1 != x2)
          {
            setPixelColor(x1,y1, GC.GetRGBGradientColor(x1) );
            x1 += signX;
          }
        return;  
      }
    
    //ANY line, but vert and hor are done above, faster
    //gradient by bigger delta, X or Y
    RGBGradientCalculator GC; //create gradient calculator
    if (deltaX > deltaY) GC.SetScale (color1,  color2,  x1, x2); //set scale according to bigger delta
                    else GC.SetScale (color1,  color2,  y1, y2);
    int error = deltaX - deltaY;
    while(x1 != x2 || y1 != y2) 
   {
        //gradient by bigger delta
        if (deltaX > deltaY) setPixelColor(x1,y1, GC.GetRGBGradientColor(x1) ); 
                        else setPixelColor(x1,y1, GC.GetRGBGradientColor(y1) ); 
        
        const int error2 = error * 2;
        //
        if(error2 > -deltaY) 
        {
            error -= deltaY;
            x1 += signX;
        }
        if(error2 < deltaX) 
        {
            error += deltaX;
            y1 += signY;
        }
    }
}

void XYMatrix::draw_line_gradient(Point P1, Point P2, CRGB color1, CRGB color2, boolean includeLastPoint) //gradient
{
  draw_line_gradient(P1.X, P1.Y, P2.X, P2.Y, color1, color2, includeLastPoint);
}


void XYMatrix::draw_rect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, CRGB color)
{
  draw_line(x1,y1, x1,y2, color, false);
  draw_line(x1,y2, x2,y2, color, false);
  draw_line(x2,y2, x2,y1, color, false);
  draw_line(x2,y1, x1,y1, color, false);
}

void XYMatrix::draw_rect(Point P1, Point P2, CRGB color)
{
  draw_rect(P1.X,P1.Y, P2.X, P2.Y, color);
}

void XYMatrix::draw_rect(RectangleWH Rect, CRGB color)
{
  draw_rect(Rect.LeftBottom.X, Rect.LeftBottom.Y, Rect.LeftBottom.X+Rect.Width, Rect.LeftBottom.Y+Rect.Height, color);
}

void XYMatrix::draw_rect(Rectangle Rect, CRGB color)
{
  draw_rect(Rect.P1.X, Rect.P1.Y, Rect.P2.X, Rect.P2.Y, color);
}

void XYMatrix::draw_fillrect(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, CRGB color)
{
  //borders check, add 6/19/202
  if (x0>= _MatrixWidth) x0=_MatrixWidth-1;
  if (x1>= _MatrixWidth) x1=_MatrixWidth-1;
  if (y0>= _MatrixHeight) y0=_MatrixHeight-1;
  if (y0>= _MatrixHeight) y0=_MatrixHeight-1;
	
  for( uint16_t yi = min(y0,y1); yi <= max(y0,y1); yi++)
  {
  draw_line(x0,yi, x1,yi, color);
  }
}

void XYMatrix::draw_fillrect(Point P1, Point P2, CRGB color)
{
  draw_fillrect(P1.X,P1.Y, P2.X, P2.Y, color);
}

void XYMatrix::draw_fillrect(RectangleWH Rect, CRGB color)
{
  draw_fillrect(Rect.LeftBottom.X, Rect.LeftBottom.Y, Rect.LeftBottom.X+Rect.Width, Rect.LeftBottom.Y+Rect.Height, color);
}

void XYMatrix::draw_fillrect(Rectangle Rect, CRGB color)
{
  draw_fillrect(Rect.P1.X, Rect.P1.Y, Rect.P2.X, Rect.P2.Y, color);
}

/**************************************************************************/
/*!
    Copied from Adafruit_GFX library
    
    @brief    Quarter-circle drawer, used to do circles and roundrects
    @param    x0   Center-point x coordinate
    @param    y0   Center-point y coordinate
    @param    r   Radius of circle
    @param    cornername  Maskbit to indicate which quarters of the circle: 
                          0x1 (left-bottom), 0x2 (right-bottom) 0x4 (right-top) 0x8 (left-top)
    @param    color color
*/
void XYMatrix::draw_quarterCircle(int16_t x0, int16_t y0, int16_t r, uint16_t cornername, CRGB color, boolean includeEdges) 
{
    int16_t f     = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x     = 0;
    int16_t y     = r;
   if (includeEdges)
     {
      if ( (cornername & 0x01) || (cornername & 0x08) ) {setPixelColor(x0-r, y0  , color);} //left point
      if ( (cornername & 0x04) || (cornername & 0x08) ) {setPixelColor(x0  , y0+r, color);} //top point
      if ( (cornername & 0x02) || (cornername & 0x04) ) {setPixelColor(x0+r, y0  , color);} //right point
      if ( (cornername & 0x01) || (cornername & 0x02) ) {setPixelColor(x0  , y0-r, color);} //bottom point
     }
    while (x<y) 
    {
        if (f >= 0) 
        {
            y--;
            ddF_y += 2;
            f     += ddF_y;
        }
        x++;
        ddF_x += 2;
        f     += ddF_x;
        if (cornername & 0x01) 
        {
          //left-bottom
          setPixelColor(x0 - y, y0 - x, color);
          setPixelColor(x0 - x, y0 - y, color);
        }
        if (cornername & 0x02) 
        {
          //right-bottom
          setPixelColor(x0 + x, y0 - y, color);
          setPixelColor(x0 + y, y0 - x, color);
        }

        if (cornername & 0x04) 
        {
          //right-top
          setPixelColor(x0 + x, y0 + y, color);
          setPixelColor(x0 + y, y0 + x, color);
        }

        if (cornername & 0x08) 
        {
          //left-top
          setPixelColor(x0 - y, y0 + x, color);
          setPixelColor(x0 - x, y0 + y, color);
        }
    }
}

/**************************************************************************/
/*!
    Copied from Adafruit_GFX library
    
    @brief    Quarter-circle drawer with fill, used to do circles and roundrects
    @param    x0   Center-point x coordinate
    @param    y0   Center-point y coordinate
    @param    r   Radius of circle
    @param    cornername  Maskbit to indicate which quarters of the circle: 
                          0x1 (left-bottom), 0x2 (right-bottom) 0x4 (right-top) 0x8 (left-top)
    @param    color color
*/
void XYMatrix::draw_quarterFillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t cornername, CRGB color, boolean includeEdges) 
{
    int16_t f     = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x     = 0;
    int16_t y     = r;
   if (includeEdges)
     {
      if ( (cornername & 0x01) || (cornername & 0x08) ) {draw_line(x0-r, y0,   x0, y0, color);} //left hor line
      if ( (cornername & 0x04) || (cornername & 0x08) ) {draw_line(x0  , y0+r, x0, y0, color);} //top vert line
      if ( (cornername & 0x02) || (cornername & 0x04) ) {draw_line(x0+r, y0  , x0, y0, color);} //right hor line
      if ( (cornername & 0x01) || (cornername & 0x02) ) {draw_line(x0  , y0-r, x0, y0, color);} //bottom vert line
     }
    while (x<y) 
    {
        if (f >= 0) 
        {
            y--;
            ddF_y += 2;
            f     += ddF_y;
        }
        x++;
        ddF_x += 2;
        f     += ddF_x;
        if (cornername & 0x01) 
        {
          //left-bottom
          draw_line(x0 - y, y0 - x, x0 - 1, y0 - x, color); //hor.line
          draw_line(x0 - x, y0 - y, x0 - 1, y0 - y, color); //hor.line
        }
        if (cornername & 0x02) 
        {
          //right-bottom
         draw_line(x0 + x, y0 - y, x0 + 1, y0 - y, color); //hor.line
         draw_line(x0 + y, y0 - x, x0 + 1, y0 - x, color); //hor.line
        }
        if (cornername & 0x04) 
        {
          //right-top
          draw_line(x0 + x, y0 + y, x0 + 1, y0 + y, color); //hor.line
          draw_line(x0 + y, y0 + x, x0 + 1, y0 + x, color); //hor.line
        }
        if (cornername & 0x08) 
        {
          //left-top
          draw_line(x0 - y, y0 + x, x0 - 1, y0 + x, color); //hor.line
          draw_line(x0 - x, y0 + y, x0 - 1, y0 + y, color); //hor.line
        }
    }
}

void XYMatrix::draw_circle(int16_t x0, int16_t y0, int16_t r, CRGB color)
{
  draw_quarterCircle(x0, y0, r, 0x0f, color, true); 
}

void XYMatrix::draw_fillCircle(int16_t x0, int16_t y0, int16_t r, CRGB color)
{
  draw_quarterFillCircle(x0, y0, r, 0x0f, color, true); 
}


void XYMatrix::draw_2DRainbow(RectangleWH Rect, byte OriginHue, Point origin, int8_t XDeltaHue, int8_t YDeltaHue)
{
  OriginHue = OriginHue - ((origin.X-Rect.LeftBottom.X)*XDeltaHue) - ((origin.Y-Rect.LeftBottom.Y)*YDeltaHue);
  byte lineStartHue = OriginHue;
  for( byte y = Rect.LeftBottom.Y; y < Rect.LeftBottom.Y+Rect.Height+1; y++) //number of dots is (Height+1)
    {
    byte pixelHue = lineStartHue;      
    for( byte x = Rect.LeftBottom.X; x < Rect.LeftBottom.X+Rect.Width+1; x++) //number of dots is (Width+1)
      {
      //_leds[ XY(x, y) ] = CHSV( pixelHue, 255, 255); //no bounds check
      setPixelColor(x, y, CHSV( pixelHue, 255, 255) ); //bounds check
      pixelHue += XDeltaHue;
      }
    lineStartHue += YDeltaHue;
    }
}

void XYMatrix::draw_2DRainbow(Rectangle Rect, byte OriginHue, Point origin, int8_t XDeltaHue, int8_t YDeltaHue)
{
  RectangleWH RWH = RectangleToRectangleWH(Rect);
  draw_2DRainbow( RWH, OriginHue, origin, XDeltaHue, YDeltaHue);
}

void XYMatrix::draw_2DRainbow(byte OriginHue, int8_t XDeltaHue, int8_t YDeltaHue)
{
  struct RectangleWH RWH = {Point(0,0), _MatrixWidth-1, _MatrixHeight-1};
  draw_2DRainbow(RWH, OriginHue, Point(0,0), XDeltaHue, YDeltaHue);
}


void XYMatrix::draw_2DRainbow(byte OriginHue, int originX, int originY, int8_t XDeltaHue, int8_t YDeltaHue)
{
  OriginHue = OriginHue - (originX*XDeltaHue) - (originY*YDeltaHue);
  draw_2DRainbow(OriginHue, XDeltaHue, YDeltaHue);
}

void XYMatrix::draw_2DRainbow(byte OriginHue, Point origin, int8_t XDeltaHue, int8_t YDeltaHue)
{
 draw_2DRainbow(OriginHue, origin.X, origin.Y, XDeltaHue, YDeltaHue);
}


void XYMatrix::draw_2DGradient(RectangleWH Rect, CRGB LeftBottomColor, CRGB LeftTopColor, CRGB RightBottomColor, CRGB RightTopColor)
{
  //added 5/17/2020 protection to handle out of matrix bounds
  if (Rect.LeftBottom.X >= _MatrixWidth)  return;
  if (Rect.LeftBottom.Y >= _MatrixHeight) return;
  if ((Rect.LeftBottom.X+Rect.Width) >= _MatrixWidth)   {Rect.Width  = (_MatrixWidth  - Rect.LeftBottom.X-1);}
  if ((Rect.LeftBottom.Y+Rect.Height) >= _MatrixHeight) {Rect.Height = (_MatrixHeight - Rect.LeftBottom.Y-1);}
  //
  RGBGradientCalculator LeftGradient  (LeftBottomColor,  LeftTopColor,  Rect.LeftBottom.Y, Rect.LeftBottom.Y+Rect.Height);
  RGBGradientCalculator RightGradient (RightBottomColor, RightTopColor, Rect.LeftBottom.Y, Rect.LeftBottom.Y+Rect.Height);
  for( byte y = Rect.LeftBottom.Y; y < Rect.LeftBottom.Y+Rect.Height+1; y++) //number of dots is (Height+1)
    {
    CRGB cl = LeftGradient.GetRGBGradientColor(y);
    CRGB cr = RightGradient.GetRGBGradientColor(y);
    fill_gradient_RGB(_leds,  XY(Rect.LeftBottom.X,y), cl, XY(Rect.LeftBottom.X+Rect.Width,y), cr ); 
    }
}

void XYMatrix::draw_2DGradient(Rectangle Rect, CRGB LeftBottomColor, CRGB LeftTopColor, CRGB RightBottomColor, CRGB RightTopColor)
{
  RectangleWH RWH = RectangleToRectangleWH(Rect);
  draw_2DGradient ( RWH, LeftBottomColor, LeftTopColor, RightBottomColor, RightTopColor );
}

void XYMatrix::draw_2DGradient(CRGB LeftBottomColor, CRGB LeftTopColor, CRGB RightBottomColor, CRGB RightTopColor)
{
  struct RectangleWH R = {Point(0,0), _MatrixWidth-1, _MatrixHeight-1};
  draw_2DGradient(R, LeftBottomColor, LeftTopColor, RightBottomColor, RightTopColor);
}

//shifts
CRGB XYMatrix::ShiftHorLineLeft(int16_t X0, int16_t X1, int16_t Y, CRGB colorIN) //X0<=X1
{
  CRGB tmp_c, ret_c;
  ret_c = getPixelColor(X0, Y);
  if (X0<=X1)
    {
    for (uint16_t x = X0+1; x <= X1 ; x++) //from X max to X min
      {
      tmp_c = getPixelColor(x, Y);
      setPixelColor(x-1, Y, tmp_c);
      }
    setPixelColor(X1, Y, colorIN);
    }
  return ret_c;
}

void XYMatrix::Shift_RectLeft(RectangleWH Rect, CRGB ColorArrIn[] )
{
  byte i=0;
  for( byte y = Rect.LeftBottom.Y; y < Rect.LeftBottom.Y+Rect.Height+1; y++)
  {
    ShiftHorLineLeft(Rect.LeftBottom.X, Rect.LeftBottom.X+Rect.Width, y, ColorArrIn[i++]);
  }
}

void XYMatrix::Shift_RectLeft(Rectangle Rect, CRGB ColorArrIn[] )
{
  RectangleWH RWH = RectangleToRectangleWH(Rect);
  Shift_RectLeft( RWH, ColorArrIn );
}

void XYMatrix::Shift_RectLeft( CRGB ColorArrIn[] ) //whole matrix
{
  struct RectangleWH RWH = {Point(0,0), _MatrixWidth-1, _MatrixHeight-1};
  Shift_RectLeft( RWH, ColorArrIn );
}

void XYMatrix::Shift_RectLeftRound(RectangleWH Rect)
{
  CRGB c;
  for( byte y = Rect.LeftBottom.Y; y < Rect.LeftBottom.Y+Rect.Height+1; y++)
  {
    c = getPixelColor(Rect.LeftBottom.X, y);
    ShiftHorLineLeft(Rect.LeftBottom.X, Rect.LeftBottom.X+Rect.Width, y, c);
  }
}

void XYMatrix::Shift_RectLeftRound(Rectangle Rect)
{
  RectangleWH RWH = RectangleToRectangleWH(Rect);
  Shift_RectLeftRound( RWH );
}

void XYMatrix::Shift_RectLeftRound( ) //whole matrix
{
  struct RectangleWH RWH = {Point(0,0), _MatrixWidth-1, _MatrixHeight-1};
  Shift_RectLeftRound( RWH );
}

//shifts left, single color
void XYMatrix::Shift_RectLeft(RectangleWH Rect, CRGB ColorIn)
{
  for( byte y = Rect.LeftBottom.Y; y < Rect.LeftBottom.Y+Rect.Height+1; y++)
  {
    ShiftHorLineLeft(Rect.LeftBottom.X, Rect.LeftBottom.X+Rect.Width, y, ColorIn);
  }
}

void XYMatrix::Shift_RectLeft(CRGB ColorIn)
{
struct RectangleWH RWH = {Point(0,0), _MatrixWidth-1, _MatrixHeight-1};
Shift_RectLeft(RWH, ColorIn);
}

//shift right
CRGB XYMatrix::ShiftHorLineRight(int16_t X0, int16_t X1, int16_t Y, CRGB colorIN) //X0<=X1
{
  CRGB tmp_c, ret_c;
  ret_c = getPixelColor(X1, Y);
  if (X0<=X1)
    {
    for (int16_t x = X1-1; x >= X0 ; x--) //from X max to X min
      {
      tmp_c = getPixelColor(x, Y);
      setPixelColor(x+1, Y, tmp_c);
      }
    setPixelColor(X0, Y, colorIN);
    }
  return ret_c;
}

void XYMatrix::Shift_RectRight(RectangleWH Rect, CRGB ColorArrIn[] )
{
  byte i=0;
  for( byte y = Rect.LeftBottom.Y; y < Rect.LeftBottom.Y+Rect.Height+1; y++)
  {
    ShiftHorLineRight(Rect.LeftBottom.X, Rect.LeftBottom.X+Rect.Width, y, ColorArrIn[i++]);
  }
}

//shifts right round
void XYMatrix::Shift_RectRightRound(RectangleWH Rect)
{
  CRGB c;
  for (byte y = Rect.LeftBottom.Y; y < Rect.LeftBottom.Y+Rect.Height+1; y++)
    {
    c = getPixelColor(Rect.LeftBottom.X+Rect.Width, y);
    ShiftHorLineRight(Rect.LeftBottom.X, Rect.LeftBottom.X+Rect.Width, y, c);
    }
}

//shifts right, single color
void XYMatrix::Shift_RectRight(RectangleWH Rect, CRGB ColorIn)
{
  for( byte y = Rect.LeftBottom.Y; y < Rect.LeftBottom.Y+Rect.Height+1; y++)
  {
    ShiftHorLineRight(Rect.LeftBottom.X, Rect.LeftBottom.X+Rect.Width, y, ColorIn);
  }
}

void XYMatrix::Shift_RectRight(CRGB ColorIn)
{
struct RectangleWH RWH = {Point(0,0), _MatrixWidth-1, _MatrixHeight-1};
Shift_RectRight(RWH, ColorIn);
}

//shifts up
CRGB XYMatrix::ShiftVertLineUp(int16_t X, int16_t Y0, int16_t Y1, CRGB colorIN) //helper function, Y0<=Y1, returns colorOUT (not used for now)
{
  CRGB tmp_c, ret_c;
  ret_c = getPixelColor(X, Y1);
  if (Y0<=Y1)
    {
    for (int16_t y = Y1-1; y >= Y0 ; y--) //from Y max to Y min
      {
      tmp_c = getPixelColor(X, y);
      setPixelColor(X, y+1, tmp_c);
      }
    setPixelColor(X, Y0, colorIN);
    }
  return ret_c;
}

void XYMatrix::Shift_RectUp(RectangleWH Rect, CRGB ColorArrIn[] )
{
  byte i=0;
  for( byte x = Rect.LeftBottom.X; x < Rect.LeftBottom.X+Rect.Width+1; x++)
  {
    ShiftVertLineUp(x, Rect.LeftBottom.Y, Rect.LeftBottom.Y+Rect.Height, ColorArrIn[i++]);
  }
}

//shifts up round
void XYMatrix::Shift_RectUpRound(RectangleWH Rect)
{
  CRGB c;
  for (byte x = Rect.LeftBottom.X; x < Rect.LeftBottom.X+Rect.Width+1; x++)
    {
    c = getPixelColor(x, Rect.LeftBottom.Y+Rect.Height);
    ShiftVertLineUp(x, Rect.LeftBottom.Y, Rect.LeftBottom.Y+Rect.Height, c);
    }
}

//shifts up, single color
void XYMatrix::Shift_RectUp(RectangleWH Rect, CRGB ColorIn)
{  
  for( byte x = Rect.LeftBottom.X; x < Rect.LeftBottom.X+Rect.Width+1; x++)
  {
    ShiftVertLineUp(x, Rect.LeftBottom.Y, Rect.LeftBottom.Y+Rect.Height, ColorIn);
  }
}

void XYMatrix::Shift_RectUp(CRGB ColorIn)
{  
struct RectangleWH RWH = {Point(0,0), _MatrixWidth-1, _MatrixHeight-1};
Shift_RectUp(RWH, ColorIn);
}

//shifts down
CRGB XYMatrix::ShiftVertLineDown(int16_t X, int16_t Y0, int16_t Y1, CRGB colorIN) //helper function, Y0<=Y1, returns colorOUT (not used for now)
{
  CRGB tmp_c, ret_c;
  ret_c = getPixelColor(X, Y0);
  if (Y0<=Y1)
    {
    for (uint16_t y = Y0+1; y <= Y1 ; y++) //from Y max to Y min
      {
      tmp_c = getPixelColor(X, y);
      setPixelColor(X, y-1, tmp_c);
      }
    setPixelColor(X, Y1, colorIN);
    }
  return ret_c;
}

void XYMatrix::Shift_RectDown(RectangleWH Rect, CRGB ColorArrIn[] )
{
  byte i=0;
  for( byte x = Rect.LeftBottom.X; x < Rect.LeftBottom.X+Rect.Width+1; x++)
  {
    ShiftVertLineDown(x, Rect.LeftBottom.Y, Rect.LeftBottom.Y+Rect.Height, ColorArrIn[i++]);
  }
}

//shifts down round
void XYMatrix::Shift_RectDownRound(RectangleWH Rect)
{
  CRGB c;
  for (byte x = Rect.LeftBottom.X; x < Rect.LeftBottom.X+Rect.Width+1; x++)
    {
    c = getPixelColor(x, Rect.LeftBottom.Y);
    ShiftVertLineDown(x, Rect.LeftBottom.Y, Rect.LeftBottom.Y+Rect.Height, c);
    }
}

//shifts down, single color
void XYMatrix::Shift_RectDown(RectangleWH Rect, CRGB ColorIn)
{
  for( byte x = Rect.LeftBottom.X; x < Rect.LeftBottom.X+Rect.Width+1; x++)
  {
    ShiftVertLineDown(x, Rect.LeftBottom.Y, Rect.LeftBottom.Y+Rect.Height, ColorIn);
  }
}

void XYMatrix::Shift_RectDown(CRGB ColorIn)
{
struct RectangleWH RWH = {Point(0,0), _MatrixWidth-1, _MatrixHeight-1};
Shift_RectDown(RWH, ColorIn);
}

//shifts round with direction
void XYMatrix::Shift_RectRoundDir(RectangleWH Rect, uint16_t Direction) //0:Up, 1:UpRight, 2:Right, 3:DownRight, 4:Down, 5:DownLeft, 6:Left, 7:UpLeft
{
  CRGB c;
  switch (Direction)
  {
    case 0:  //Up
      Shift_RectUpRound(Rect);
      break;

    case 1:  //UpRight
      Shift_RectUpRound(Rect);
      Shift_RectRightRound(Rect);
      break;  
    
    case 2:  //Right
      Shift_RectRightRound(Rect);
      break;
    
    case 3:  //DownRight
      Shift_RectDownRound(Rect);
      Shift_RectRightRound(Rect);
      break;  

    case 4:  //Down
      Shift_RectDownRound(Rect);
      break;

    case 5:  //DownLeft
      Shift_RectDownRound(Rect);
      Shift_RectLeftRound(Rect);
      break;  
    
    case 6:  //Left
      Shift_RectLeftRound(Rect);
      break;
    
    case 7:  //UpLeft
      Shift_RectUpRound(Rect);
      Shift_RectLeftRound(Rect);
      break;  
  }//end of switch
}

void XYMatrix::Shift_RectRoundDir(uint16_t Direction)  //whole matrix  //0:Up, 1:UpRight, 2:Right, 3:DownRight, 4:Down, 5:DownLeft, 6:Left, 7:UpLeft
{
  struct RectangleWH RWH = {Point(0,0), _MatrixWidth-1, _MatrixHeight-1};
  Shift_RectRoundDir( RWH, Direction );
}

//shifts (no round) with direction 
void XYMatrix::Shift_RectDir(RectangleWH Rect, uint16_t Direction, CRGB ColorArrInVertShift[], CRGB ColorArrInHorShift[] ) //0:Up, 1:UpRight, 2:Right, 3:DownRight, 4:Down, 5:DownLeft, 6:Left, 7:UpLeft
{
  switch (Direction)
  {
    case 0:  //Up
      Shift_RectUp(Rect, ColorArrInVertShift);
      break;

    case 1:  //UpRight
      Shift_RectUp(Rect, ColorArrInVertShift);
      Shift_RectRight(Rect, ColorArrInHorShift);
      break;  
    
    case 2:  //Right
      Shift_RectRight(Rect, ColorArrInHorShift);
      break;
    
    case 3:  //DownRight
      Shift_RectDown(Rect, ColorArrInVertShift);
      Shift_RectRight(Rect, ColorArrInHorShift);
      break;  

    case 4:  //Down
      Shift_RectDown(Rect, ColorArrInVertShift);
      break;

    case 5:  //DownLeft
      Shift_RectDown(Rect, ColorArrInVertShift);
      Shift_RectLeft(Rect, ColorArrInHorShift);
      break;  
    
    case 6:  //Left
      Shift_RectLeft(Rect, ColorArrInHorShift);
      break;
    
    case 7:  //UpLeft
      Shift_RectUp(Rect, ColorArrInVertShift);
      Shift_RectLeft(Rect, ColorArrInHorShift);
      break;  
  }//end of switch
}

void XYMatrix::Shift_RectDir(uint16_t Direction, CRGB ColorArrInVertShift[], CRGB ColorArrInHorShift[] ) //whole matrix //0:Up, 1:UpRight, 2:Right, 3:DownRight, 4:Down, 5:DownLeft, 6:Left, 7:UpLeft
{
  struct RectangleWH RWH = {Point(0,0), _MatrixWidth-1, _MatrixHeight-1};
  Shift_RectDir(RWH, Direction, ColorArrInVertShift, ColorArrInHorShift );
}

void XYMatrix::Shift_RectDir(RectangleWH Rect, uint16_t Direction, CRGB ColorInVertShift, CRGB ColorInHorShift ) //single colors //0:Up, 1:UpRight, 2:Right, 3:DownRight, 4:Down, 5:DownLeft, 6:Left, 7:UpLeft
{
  switch (Direction)
  {
    case 0:  //Up
      Shift_RectUp(Rect, ColorInVertShift);
      break;

    case 1:  //UpRight
      Shift_RectUp(Rect, ColorInVertShift);
      Shift_RectRight(Rect, ColorInHorShift);
      break;  
    
    case 2:  //Right
      Shift_RectRight(Rect, ColorInHorShift);
      break;
    
    case 3:  //DownRight
      Shift_RectDown(Rect, ColorInVertShift);
      Shift_RectRight(Rect, ColorInHorShift);
      break;  

    case 4:  //Down
      Shift_RectDown(Rect, ColorInVertShift);
      break;

    case 5:  //DownLeft
      Shift_RectDown(Rect, ColorInVertShift);
      Shift_RectLeft(Rect, ColorInHorShift);
      break;  
    
    case 6:  //Left
      Shift_RectLeft(Rect, ColorInHorShift);
      break;
    
    case 7:  //UpLeft
      Shift_RectUp(Rect, ColorInVertShift);
      Shift_RectLeft(Rect, ColorInHorShift);
      break;  
  }//end of switch
}

void XYMatrix::Shift_RectDir(uint16_t Direction, CRGB ColorInVertShift, CRGB ColorInHorShift ) //single colors, whole matrix //0:Up, 1:UpRight, 2:Right, 3:DownRight, 4:Down, 5:DownLeft, 6:Left, 7:UpLeft
{
  struct RectangleWH RWH = {Point(0,0), _MatrixWidth-1, _MatrixHeight-1};
  Shift_RectDir(RWH, Direction, ColorInVertShift, ColorInHorShift );
}

//Plasma-like effects, based on FastLED inoise() function - “fixed point implementation of perlin’s Simplex Noise”
void XYMatrix::draw_2DPlasma(RectangleWH Rect, uint16_t NoiseSpaceX, uint16_t NoiseSpaceY, uint16_t NoiseSpaceZ, uint16_t NoiseScale, boolean UseBriControl, boolean ExpandDR)
{
  for( int x = Rect.LeftBottom.X; x < Rect.LeftBottom.X+Rect.Width+1; x++) //number of dots is (Width+1)
  {
    int nx =  (NoiseScale*x) + NoiseSpaceX;
    for( int y = Rect.LeftBottom.Y; y < Rect.LeftBottom.Y+Rect.Height+1; y++) //number of dots is (Height+1)
    {
    int ny = (NoiseScale*y) + NoiseSpaceY;
    uint16_t NoiseValue = inoise8(nx, ny, NoiseSpaceZ);

    if (ExpandDR)
      {
      // The range of the inoise8 function is roughly 16-238.
      // These two operations expand those values out to roughly 0..255
      // You can comment them out if you want the raw noise data.
      NoiseValue = qsub8(NoiseValue, 16);
      NoiseValue = qadd8(NoiseValue, scale8(NoiseValue, 39));
      }

	uint16_t bri;
	if (UseBriControl)
	  {
      //optional second (mirrored) parameter use as a brightness
      bri = inoise8(ny, nx, NoiseSpaceZ);
	  if (ExpandDR)
        {
        // brighten up, as the color palette itself often contains the 
        // light/dark dynamic range desired
        if( bri > 127 ) {bri = 255;} else {bri = dim8_raw( bri * 2);}
		}
	  }
	  else 
	    {bri = 255;}
	//set pixel color
	    //for paletet usage
        //CRGB color = ColorFromPalette( PaletteToUse, NoiseValue, bri, LINEARBLEND); //LINEARBLEND NOBLEND
        //setPixelColor(x, y, color);
	//for non-palette usage
    setPixelColor(x, y, CHSV(NoiseValue, 255, bri));
    }
  }
}

void XYMatrix::draw_2DPlasma(Rectangle Rect, uint16_t NoiseSpaceX, uint16_t NoiseSpaceY, uint16_t NoiseSpaceZ, uint16_t NoiseScale, boolean UseBriControl, boolean ExpandDR)
{
  RectangleWH RWH = RectangleToRectangleWH(Rect);
  draw_2DPlasma (RWH, NoiseSpaceX, NoiseSpaceY, NoiseSpaceZ, NoiseScale, UseBriControl, ExpandDR);
}

void XYMatrix::draw_2DPlasma(uint16_t NoiseSpaceX, uint16_t NoiseSpaceY, uint16_t NoiseSpaceZ, uint16_t NoiseScale, boolean UseBriControl, boolean ExpandDR)
{
  struct RectangleWH R = {Point(0,0), _MatrixWidth-1, _MatrixHeight-1};
  draw_2DPlasma (R, NoiseSpaceX, NoiseSpaceY, NoiseSpaceZ, NoiseScale, UseBriControl, ExpandDR);
}

//Plasma-like Palette effects, based on FastLED inoise() function - “fixed point implementation of perlin’s Simplex Noise” 
void XYMatrix::draw_2DPlasmaPal(RectangleWH Rect, CRGBPalette16 PalToUse, uint16_t NoiseSpaceX, uint16_t NoiseSpaceY, uint16_t NoiseSpaceZ, uint16_t NoiseScale, boolean UseBriControl, boolean ExpandDR, TBlendType PalBlendType)
{
  for( int x = Rect.LeftBottom.X; x < Rect.LeftBottom.X+Rect.Width+1; x++) //number of dots is (Width+1)
  {
    int nx =  (NoiseScale*x) + NoiseSpaceX;
    for( int y = Rect.LeftBottom.Y; y < Rect.LeftBottom.Y+Rect.Height+1; y++) //number of dots is (Height+1)
    {
    int ny = (NoiseScale*y) + NoiseSpaceY;
    uint16_t NoiseValue = inoise8(nx, ny, NoiseSpaceZ);

    if (ExpandDR)
      {
      // The range of the inoise8 function is roughly 16-238.
      // These two operations expand those values out to roughly 0..255
      // You can comment them out if you want the raw noise data.
      NoiseValue = qsub8(NoiseValue, 16);
      NoiseValue = qadd8(NoiseValue, scale8(NoiseValue, 39));
      }

	uint16_t bri;
	if (UseBriControl)
	  {
      //optional second (mirrored) parameter use as a brightness
      bri = inoise8(ny, nx, NoiseSpaceZ);
	  if (ExpandDR)
        {
        // brighten up, as the color palette itself often contains the 
        // light/dark dynamic range desired
        if( bri > 127 ) {bri = 255;} else {bri = dim8_raw( bri * 2);}
		}
	  }
	  else 
	    {bri = 255;}
	//set pixel color
	//for paletet usage	
    CRGB color = ColorFromPalette( PalToUse, NoiseValue, bri, PalBlendType); //LINEARBLEND, NOBLEND
    setPixelColor(x, y, color);
	    //for non-paletet usage	
	    //setPixelColor(x, y, CHSV(NoiseValue, 255, bri));
    }
  }	
}

void XYMatrix::draw_2DPlasmaPal(Rectangle Rect, CRGBPalette16 PalToUse, uint16_t NoiseSpaceX, uint16_t NoiseSpaceY, uint16_t NoiseSpaceZ, uint16_t NoiseScale, boolean UseBriControl, boolean ExpandDR, TBlendType PalBlendType)
{
  RectangleWH RWH = RectangleToRectangleWH(Rect);
  draw_2DPlasmaPal(Rect, PalToUse, NoiseSpaceX, NoiseSpaceY, NoiseSpaceZ, NoiseScale, UseBriControl, ExpandDR, PalBlendType);
}

void XYMatrix::draw_2DPlasmaPal(CRGBPalette16 PalToUse, uint16_t NoiseSpaceX, uint16_t NoiseSpaceY, uint16_t NoiseSpaceZ, uint16_t NoiseScale, boolean UseBriControl, boolean ExpandDR, TBlendType PalBlendType)
{
  struct RectangleWH R = {Point(0,0), _MatrixWidth-1, _MatrixHeight-1};
  draw_2DPlasmaPal(R, PalToUse, NoiseSpaceX, NoiseSpaceY, NoiseSpaceZ, NoiseScale, UseBriControl, ExpandDR, PalBlendType);
}


 //End of XYMatrix Class
