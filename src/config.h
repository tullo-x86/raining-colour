#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "pixeltypes.h"

#define NUM_LEDS 32
#define MAX_BRIGHTNESS 64

inline void assignGreater(unsigned char *storage, unsigned char comparison)
{
	if (comparison > *storage) *storage = comparison;
}

// Shouldn't modify below this line

extern struct CRGB frameBuffer[NUM_LEDS];

#endif
