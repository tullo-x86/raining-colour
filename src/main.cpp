// Rain
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

	SparksPattern patterns[NUM_STRIPS] =
	{
		SparksPattern(frameBuffer + (LEDS_PER_STRIP * 0), LEDS_PER_STRIP, 3, 18, 28, 128, 24),
		SparksPattern(frameBuffer + (LEDS_PER_STRIP * 1), LEDS_PER_STRIP, 3,  9, 28, 128, 12),
		SparksPattern(frameBuffer + (LEDS_PER_STRIP * 2), LEDS_PER_STRIP, 3, 12, 28, 128, 16),
		SparksPattern(frameBuffer + (LEDS_PER_STRIP * 3), LEDS_PER_STRIP, 3, 18, 28, 128, 24),
		SparksPattern(frameBuffer + (LEDS_PER_STRIP * 4), LEDS_PER_STRIP, 3, 10, 28, 128, 20)
	};

    while(1) {
    	for (unsigned char i = 0; i < NUM_STRIPS; i++)
    	{
    		patterns[i].Logic();
    		patterns[i].Render();
    	}

    	FastLED.show();
        _delay_ms(35);
    }
}
