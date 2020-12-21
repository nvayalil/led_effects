#include "bouncing_balls.h"
#include "lights.h"

#include <math.h>
#include <stdbool.h>
#include <time.h>

long millis()
{
    static struct timespec t1;    
    clock_gettime(CLOCK_MONOTONIC, &t1);
    return t1.tv_nsec / (1000 * 1000);
}

extern volatile bool running; 

void BouncingBalls(uint8_t red, uint8_t green, uint8_t blue, uint8_t BallCount) 
{
    float Gravity = -9.81;
    int StartHeight = 1;

    float Height[BallCount];
    float ImpactVelocityStart = sqrt( -2 * Gravity * StartHeight );
    float ImpactVelocity[BallCount];
    float TimeSinceLastBounce[BallCount];
    int   Position[BallCount];
    long  ClockTimeSinceLastBounce[BallCount];
    float Dampening[BallCount];

    for (int i = 0 ; i < BallCount ; i++) 
    {  
        ClockTimeSinceLastBounce[i] = millis();
        Height[i] = StartHeight;
        Position[i] = 0;
        ImpactVelocity[i] = ImpactVelocityStart;
        TimeSinceLastBounce[i] = 0;
        Dampening[i] = 0.90 - ((float) i)/pow(BallCount, 2);
    }

    while (running) 
    {
        for (int i = 0 ; i < BallCount ; i++) 
        {
            TimeSinceLastBounce[i] =  millis() - ClockTimeSinceLastBounce[i];
            Height[i] = 0.5 * Gravity * pow( TimeSinceLastBounce[i]/1000 , 2.0 ) + ImpactVelocity[i] * TimeSinceLastBounce[i]/1000;
 
            if ( Height[i] < 0 )
            {                      
                Height[i] = 0;
                ImpactVelocity[i] = Dampening[i] * ImpactVelocity[i];
                ClockTimeSinceLastBounce[i] = millis();
 
                if ( ImpactVelocity[i] < 0.01 )
                {
                    ImpactVelocity[i] = ImpactVelocityStart;
                }
            }
            Position[i] = round( Height[i] * (LED_COUNT - 1) / StartHeight);
        }
 
        for (int i = 0 ; i < BallCount ; i++)
            set_pixel(Position[i], red, green, blue);
   
        show_strip();
        set_all(0, 0, 0);
    }
}