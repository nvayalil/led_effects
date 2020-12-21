#ifndef _LIGHTS_EFFECTS_H_
#define _LIGHTS_EFFECTS_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

void NewKITT(uint8_t red, uint8_t green, uint8_t blue, int EyeSize, int SpeedDelay, int ReturnDelay);
void rainbowCycle(int SpeedDelay);
void TwinkleRandom(int Count, int SpeedDelay, bool OnlyOne);

#endif