// Luminate: generic lighting doohickey
// Author: Daniel Tullemans / "LuminousElement"
// Created 2014

#include "FastLED.h"
#include <string.h> /* memset */
#include "config.h"
#include "mesmer.h"
#include "bounce.h"
#include "sparkspattern.h"
#include <util/delay.h>

struct CRGB frameBuffer[NUM_LEDS];

int main()
{
	memset(frameBuffer, 0, sizeof(struct CRGB) * NUM_LEDS);
	FastLED.addLeds<NEOPIXEL, 10>(frameBuffer, NUM_LEDS);

	SparksPattern pattern(frameBuffer, LEDS_PER_STRIP, 3, 10, 28, 128, 20);

    while(1) {
    	pattern.Logic();
    	pattern.Render();
    	FastLED.show();
        _delay_ms(35);
    }
}
