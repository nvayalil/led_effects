#include "light_effects.h"
#include "lights.h"
#include <time.h>
#include <stdlib.h>
#include <math.h>

static void delay(uint32_t ms)
{
    struct timespec t = {
        .tv_sec = 0,
        .tv_nsec = ms * (1000 * 1000)
    };    
    nanosleep(&t, NULL);
}


static void CenterToOutside(uint8_t red, uint8_t green, uint8_t blue, int EyeSize, int SpeedDelay, int ReturnDelay) 
{
    for (int i = ((LED_COUNT-EyeSize)/2); i >= 0; i--) 
    {
        set_all(0, 0, 0);
   
        set_pixel(i, red/10, green/10, blue/10);
        for(int j = 1; j <= EyeSize; j++)
            set_pixel(i+j, red, green, blue);

        set_pixel(i+EyeSize+1, red/10, green/10, blue/10);   
        set_pixel(LED_COUNT-i, red/10, green/10, blue/10);

        for(int j = 1; j <= EyeSize; j++)
            set_pixel(LED_COUNT-i-j, red, green, blue);

        set_pixel(LED_COUNT-i-EyeSize-1, red/10, green/10, blue/10);
   
        show_strip();
        delay(SpeedDelay);
    }
    delay(ReturnDelay);
}

static void OutsideToCenter(uint8_t red, uint8_t green, uint8_t blue, int EyeSize, int SpeedDelay, int ReturnDelay) 
{
    for(int i = 0; i<=((LED_COUNT-EyeSize)/2); i++) {
        set_all(0,0,0);

        set_pixel(i, red/10, green/10, blue/10);
        for(int j = 1; j <= EyeSize; j++) 
            set_pixel(i+j, red, green, blue);

        set_pixel(i+EyeSize+1, red/10, green/10, blue/10);

        set_pixel(LED_COUNT-i, red/10, green/10, blue/10);
        for(int j = 1; j <= EyeSize; j++) 
            set_pixel(LED_COUNT-i-j, red, green, blue);
    
        set_pixel(LED_COUNT-i-EyeSize-1, red/10, green/10, blue/10);

        show_strip();
        delay(SpeedDelay);
    }
    delay(ReturnDelay);
}

static void LeftToRight(uint8_t red, uint8_t green, uint8_t blue, int EyeSize, int SpeedDelay, int ReturnDelay) 
{
    for(int i = 0; i < LED_COUNT-EyeSize-2; i++) 
    {
        set_all(0,0,0);
        set_pixel(i, red/10, green/10, blue/10);
        for(int j = 1; j <= EyeSize; j++) 
        set_pixel(i+j, red, green, blue);
        
        set_pixel(i+EyeSize+1, red/10, green/10, blue/10);
        show_strip();
        delay(SpeedDelay);
    }
    delay(ReturnDelay);
}

static void RightToLeft(uint8_t red, uint8_t green, uint8_t blue, int EyeSize, int SpeedDelay, int ReturnDelay) 
{
    for(int i = LED_COUNT-EyeSize-2; i > 0; i--) 
    {
        set_all(0,0,0);
        set_pixel(i, red/10, green/10, blue/10);
        for(int j = 1; j <= EyeSize; j++) 
        set_pixel(i+j, red, green, blue);
        
        set_pixel(i+EyeSize+1, red/10, green/10, blue/10);
        show_strip();
        delay(SpeedDelay);
    }
    delay(ReturnDelay);
}

void NewKITT(uint8_t red, uint8_t green, uint8_t blue, int EyeSize, int SpeedDelay, int ReturnDelay)
{
    RightToLeft(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
    LeftToRight(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
    OutsideToCenter(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
    CenterToOutside(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
    LeftToRight(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
    RightToLeft(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
    OutsideToCenter(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
    CenterToOutside(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
}

/**
 * 
 *  Rainbow Cycle
 * 
 */
uint8_t * Wheel(uint8_t WheelPos) 
{
  static uint8_t c[3];
 
    if(WheelPos < 85) 
    {
        c[0]=WheelPos * 3;
        c[1]=255 - WheelPos * 3;
        c[2]=0;
    } else if(WheelPos < 170) 
    {
        WheelPos -= 85;
        c[0]=255 - WheelPos * 3;
        c[1]=0;
        c[2]=WheelPos * 3;
    } else 
    {
        WheelPos -= 170;
        c[0]=0;
        c[1]=WheelPos * 3;
        c[2]=255 - WheelPos * 3;
    }

  return c;
}

void rainbowCycle(int SpeedDelay) 
{
    uint8_t *c;
    uint16_t i, j;

    for(j=0; j<256*5; j++) 
    { // 5 cycles of all colors on wheel
        for(i=0; i< LED_COUNT; i++) 
        {
            c = Wheel(((i * 256 / LED_COUNT) + j) & 255);
            set_pixel(i, *c, *(c+1), *(c+2));
        }
        show_strip();
        delay(SpeedDelay);
    }
}

#define LED_COUNT_MASK ( (uint32_t) (pow(2, ceil(log(LED_COUNT)/log(2)))) - 1)
uint16_t getRandomLED()
{
    uint16_t r = random() & LED_COUNT_MASK;
    if(r > LED_COUNT)
        r -= LED_COUNT;
    return r;     
}



void TwinkleRandom(int Count, int SpeedDelay, bool OnlyOne) 
{
    uint32_t color;
    set_all(0, 0, 0);

    for (int i=0; i < Count; i++) 
    {
        color = get_random_color();

        set_pixel(getRandomLED(), color >> 16, (color >> 8) & 0xFF, color & 0xFF);
        show_strip();

        delay(SpeedDelay);
        if(OnlyOne)
            set_all(0,0,0);
    }
 
    delay(SpeedDelay);
}

