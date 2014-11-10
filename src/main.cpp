// Luminate: generic lighting doohickey
// Author: Daniel Tullemans / "LuminousElement"
// Created 2014

#include "FastLED.h"
#include <string.h> /* memset */
#include "config.h"
#include "mesmer.h"
#include "bounce.h"

struct CRGB frameBuffer[NUM_LEDS];

int main()
{
	memset(frameBuffer, 0, sizeof(struct CRGB) * NUM_LEDS);

	FastLED.addLeds<NEOPIXEL, 10>(frameBuffer, NUM_LEDS);

    while(1) {
    	bounceBegin();
    	bounce(20000UL);
    	bounceEnd();

    	mesmerBegin();
    	mesmer(40000UL);
    	mesmerEnd();
    }
}
