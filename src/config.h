#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "pixeltypes.h"

#define NUM_STRIPS 5
#define LEDS_PER_STRIP 32
#define NUM_LEDS (NUM_STRIPS * LEDS_PER_STRIP)

#define MAX_BRIGHTNESS 64

inline void assignGreater(unsigned char *storage, unsigned char comparison)
{
	if (comparison > *storage) *storage = comparison;
}

// Shouldn't modify below this line

extern struct CRGB frameBuffer[NUM_LEDS];

#endif
