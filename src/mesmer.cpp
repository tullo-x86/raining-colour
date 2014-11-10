#include "mesmer.h"
#include "config.h"

#include "FastLED.h"
#include <util/delay.h>

const unsigned char mesmerFrameMs = 30;

int hueOffset = 0;
unsigned char brightness = 0;

void mesmerRotateHue()
{
	if (--hueOffset < 0) hueOffset += HUE_MAX_RAINBOW;
}

void mesmerRender()
{
	fill_rainbow(frameBuffer, NUM_LEDS, hueOffset, (HUE_MAX_RAINBOW + 1) / NUM_LEDS);

    FastLED.show(brightness);
}

void mesmerBegin()
{
	brightness = 0;
	while(++brightness < MAX_BRIGHTNESS) {
    	mesmerRotateHue();
		mesmerRender();
        _delay_ms(mesmerFrameMs);
	}
}

void mesmer(unsigned long lengthMs)
{
	unsigned long time = 0;
    while(time < lengthMs)
    {
    	mesmerRotateHue();
    	mesmerRender();
        _delay_ms(mesmerFrameMs);
        time += mesmerFrameMs;
    }
}

void mesmerEnd()
{
	while(--brightness) {
    	mesmerRotateHue();
		mesmerRender();
        _delay_ms(mesmerFrameMs);
	}
}
