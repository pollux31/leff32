//Libraries
//#include <FastLED.h>//https://github.com/FastLED/FastLED
#include <FastLED_NeoPixel.h>

//Constants
//#define NUM_STRIPS 1
#define NUM_LEDS 60
#define BRIGHTNESS 50
#define LED_TYPE WS2812B
#define COLOR_ORDER BRG//RGB
//#define FASTLED_ALLOW_INTERRUPTS 0
//#define FASTLED_INTERRUPT_RETRY_COUNT 1
//#define FRAMES_PER_SECOND 60
//#define COOLING 55
//#define SPARKING 120

//Parameters
const int stripPin 	= 12;

//Variables
bool gReverseDirection 	= false;

//Objects
CRGB leds[NUM_LEDS];
FastLED_NeoPixel_Variant strip(leds, NUM_LEDS);

void SetupLed() {
 	//Init led strips
 	//FastLED.addLeds<LED_TYPE, stripPin, COLOR_ORDER>(leds, NUM_LEDS);
 	//FastLED.setBrightness( 	BRIGHTNESS );
	strip.begin(FastLED.addLeds<WS2812B, stripPin, GRB>(leds, NUM_LEDS));
	strip.setBrightness(BRIGHTNESS);
}

void LedScenario(void ) { /* function ledScenario */
 	////LEDS Strip scenario
    CRGB color;
    color.setRGB(random(255), random(255), random(255));
    for (int i = 0; i < NUM_LEDS; i++) {
        //leds[i] = CRGB::Goldenrod;
        //leds[i].setRGB(255, 0, 255);
        //leds[i + 3].setRGB(255, 0, 255);
        leds[i] = color;
        leds[i + 3] = color;
        FastLED.show();
        delay(10);
        leds[i] = CRGB::Black;
        FastLED.show();
        delay(10);
 	}
}

void rainbow(unsigned long wait) {
	// iterate through all 8-bit hues, using 16-bit values for granularity
	for (unsigned long firstPixelHue = 0; firstPixelHue < 65536; firstPixelHue += 256) {
		for (unsigned int i = 0; i < strip.numPixels(); i++) {
			unsigned long pixelHue = firstPixelHue + (i * 65536UL / strip.numPixels()); // vary LED hue based on position
			strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));  // assign color, using gamma curve for a more natural look
		}
		strip.show();
		delay(wait);
	}
}