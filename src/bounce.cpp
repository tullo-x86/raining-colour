/*
 * bounce.c
 *
 *  Created on: 23 May 2014
 *      Author: tullo
 */

#include "FastLED.h"
#include "bounce.h"
#include "config.h"
#include "hsv2rgb.h"
#include <string.h> /* memset */
#include <util/delay.h>
#include <stdlib.h>

int bounceHue = 0;
unsigned char bouncePixBuf[NUM_LEDS];
#define BOUNCE_MAX_BRIGHTNESS 127
unsigned char bounceBrightness = 0;

int bounceFalloff(int pulsePosition, int pixelIndex)
{
	int difference = (pixelIndex << 8) - pulsePosition;

	long long falloff = ((long long)difference * difference >> 11);
	if (falloff > bounceBrightness) return 0;

	return bounceBrightness - falloff;
}

void bounceRenderBouncer(int position) {
	int initialPixel = position >> 8;

	assignGreater(bouncePixBuf + initialPixel, bounceFalloff(position, initialPixel));

	int nextPixel = initialPixel + 1;
	int val = bounceFalloff(position, nextPixel);
	while (val > 0) {
		assignGreater(bouncePixBuf + (nextPixel % NUM_LEDS), val);
		nextPixel++;
		val = bounceFalloff(position, nextPixel);
	}

	nextPixel = initialPixel - 1;
	val = bounceFalloff(position, nextPixel);
	while (val > 0) {
		int pixelIdx = nextPixel < 0 ? nextPixel + NUM_LEDS : nextPixel;
		assignGreater(bouncePixBuf + pixelIdx, val);
		nextPixel++;
		val = bounceFalloff(position, nextPixel);
	}
}

// Position is an 8.8 fixed point value.
int truePosition = 0;
int reflectionPosition = NUM_LEDS << 7;
int hasReflection = 1;

inline void bounceRender()
{
	memset(bouncePixBuf, 0, sizeof(unsigned char) * NUM_LEDS);
	bounceRenderBouncer(truePosition);
	if (hasReflection) bounceRenderBouncer(reflectionPosition);

	memset(frameBuffer, 0, sizeof(struct CRGB) * NUM_LEDS);

	CHSV col;
	col.h = bounceHue;
	col.s = 255;

	for (int i = 0; i < NUM_LEDS; i++)
	{
		col.v = bouncePixBuf[i];
		hsv2rgb_rainbow(col, frameBuffer[i]);
		//frameBuffer[i] = hsvToRgbInt3(bounceHue, MAX_SAT, bouncePixBuf[i]);
	}

	FastLED.show();
    //ws2812_setleds(frameBuffer, NUM_LEDS); // Blocks for ~0.7ms
}

int direction = 1;

#define SPEED 8

inline void bounceMove()
{
	truePosition += SPEED * direction;
	if(truePosition >= (NUM_LEDS << 8))
		truePosition -= (NUM_LEDS << 8);
	else if(truePosition <= 0)
		truePosition += (NUM_LEDS << 8);

	reflectionPosition -= SPEED * direction;
	if(reflectionPosition >= (NUM_LEDS << 8))
		reflectionPosition -= (NUM_LEDS << 8);
	else if(reflectionPosition <= 0)
		reflectionPosition += (NUM_LEDS << 8);
}

#define HUE_RATIO 3
int8_t moveHue = HUE_RATIO;

inline void bounceLogic()
{
	if (--moveHue <= 0)
	{
		moveHue = HUE_RATIO;
		if (++bounceHue >= HUE_MAX_RAINBOW) bounceHue -= HUE_MAX_RAINBOW;
	}

	if(hasReflection == 0)
	{
		hasReflection = (rand() & 0xFF) == 0xFF;
		if (hasReflection) reflectionPosition = truePosition;
	}
	else if (truePosition == reflectionPosition)
	{
		hasReflection = 0;
		if((rand() & 0x3) == 0x3) direction *= -1;
	}

	bounceMove();
}

inline void bounceLogicNoSplit()
{
	if (++bounceHue >= HUE_MAX_RAINBOW) bounceHue -= HUE_MAX_RAINBOW;

	bounceMove();
}

void bounce(unsigned long lengthMs)
{
	unsigned long time = 0;
    while(time < lengthMs
    	|| hasReflection)
    {
    	bounceLogic();
    	bounceRender();

        _delay_ms(4);
        time += 5; // wow, so divide, much cycle
    }
}

void bounceBegin() {
	bounceBrightness = 0;
    while(++bounceBrightness < BOUNCE_MAX_BRIGHTNESS)
    {
    	bounceLogic();
    	hasReflection = 0;
    	bounceRender();

        _delay_ms(4);
    }
}

void bounceEnd() {
    while(--bounceBrightness > 0)
    {
    	bounceLogicNoSplit();
    	bounceRender();

        _delay_ms(4);
    }
}
