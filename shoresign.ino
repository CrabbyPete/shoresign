// Do not remove the include below
#include "patterns.h"
#include <FastLED.h>

#define DATA_PIN    6
#define LED_PIN     13
#define BRIGHTNESS  100

#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB

// This is the size of the test platform

#ifdef TEST
#define COLUMNS    	 3
#define ROWS 	     64

#define HORIZONTAL  22
#define VERTICAL    10

#else

#define COLUMNS    	3
#define ROWS 	    162

#define HORIZONTAL  69
#define VERTICAL    12

#endif

#define LEFT		-1
#define RIGHT		1

#define UP			1
#define DOWN		-1

CRGB Leds[ COLUMNS * ROWS ];

struct LEDMAP {
	int outside[165];
	int middle[162];
	int inside[159];
};

int LedMap[ COLUMNS * ROWS ] = {
0, 5, 6, 11, 12, 17, 18, 23, 24, 29, 30, 35, 36, 41, 42, 47, 48, 53, 54, 59, 60, 65, 66, 71, 72, 77, 78, 83, 84, 89, 90, 95, 96, 101, 102, 107, 108, 113, 114, 119, 120, 125, 126, 131, 132, 137, 138, 143, 144, 149, 150, 155, 156, 161, 162, 167, 168, 173, 174, 179, 180, 185, 186, 191, 192, 197, 198, 203, 204, 209, 210, 212, 213, 218, 219, 224, 225, 230, 231, 236, 237, 242, 243, 245, 246, 251, 252, 257, 258, 263, 264, 269, 270, 275, 276, 281, 282, 287, 288, 293, 294, 299, 300, 305, 306, 311, 312, 317, 318, 323, 324, 329, 330, 335, 336, 341, 342, 347, 348, 353, 354, 359, 360, 365, 366, 371, 372, 377, 378, 383, 384, 389, 390, 395, 396, 401, 402, 407, 408, 413, 414, 419, 420, 425, 426, 431, 432, 437, 438, 443, 444, 449, 450, 453, 455, 456, 461, 462, 467, 468, 473, 474, 479, 480, 485,
1, 4, 7, 10, 13, 16, 19, 22, 25, 28, 31, 34, 37, 40, 43, 46, 49, 52, 55, 58, 61, 64, 67, 70, 73, 76, 79, 82, 85, 88, 91, 94, 97, 100, 103, 106, 109, 112, 115, 118, 121, 124, 127, 130, 133, 136, 139, 142, 145, 148, 151, 154, 157, 160, 163, 166, 169, 172, 175, 178, 181, 184, 187, 190, 193, 196, 199, 202, 205, 208, 211, 214, 217, 220, 223, 226, 229, 232, 235, 238, 241, 244, 247, 250, 253, 256, 259, 262, 265, 268, 271, 274, 277, 280, 283, 286, 289, 292, 295, 298, 301, 304, 307, 310, 313, 316, 319, 322, 325, 328, 331, 334, 337, 340, 343, 346, 349, 352, 355, 358, 361, 364, 367, 370, 373, 376, 379, 382, 385, 388, 391, 394, 397, 400, 403, 406, 409, 412, 415, 418, 421, 424, 427, 430, 433, 436, 439, 442, 445, 448, 451, 454, 457, 460, 463, 466, 469, 472, 475, 478, 481, 484,
2, 3, 8, 9, 14, 15, 20, 21, 26, 27, 32, 33, 38, 39, 44, 45, 50, 51, 56, 57, 62, 63, 68, 69, 74, 75, 80, 81, 86, 87, 92, 93, 98, 99, 104, 105, 110, 111, 116, 117, 122, 123, 128, 129, 134, 135, 140, 141, 146, 147, 152, 153, 158, 159, 164, 165, 170, 171, 176, 177, 182, 183, 188, 189, 194, 195, 200, 201, 206, 207, 215, 216, 221, 222, 227, 228, 233, 234, 239, 240, 248, 249, 254, 255, 260, 261, 266, 267, 272, 273, 278, 279, 284, 285, 290, 291, 296, 297, 302, 303, 308, 309, 314, 315, 320, 321, 326, 327, 332, 333, 338, 339, 344, 345, 350, 351, 356, 357, 362, 363, 368, 369, 374, 375, 380, 381, 386, 387, 392, 393, 398, 399, 404, 405, 410, 411, 416, 417, 422, 423, 428, 429, 434, 435, 440, 441, 446, 447, 452, 458, 459, 464, 465, 470, 471, 476, 477, 482, 483
};


#define MAP( c, r ) LedMap[c * ROWS + r]

int Map( int c, int r )
{
	if ( c == 0 )
		return r;
	if ( c == 1 )
		return r + 165;
	else
		return r + 327;
}

#define STRING 1

#ifdef STRING
void initMap(void)
{
	for ( int i=0; i< COLUMNS * ROWS ; i++ )
		LedMap[i] = i;
}

#else
void initMap(void) {
}
#endif

int timer1_counter;
int timercount = 0;

void statusTimer(void)
{
	pinMode(LED_PIN, OUTPUT);

	noInterrupts();           // disable all interrupts
	TCCR1A = 0;
	TCCR1B = 0;

	timer1_counter = 53036;   // preload timer 65536-16MHz/256/2Hz

	TCNT1 = timer1_counter;   // preload timer
	TCCR1B |= (1 << CS12);    // 256 prescaler
	TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
	interrupts();             // enable all interrupts
}

ISR(TIMER1_OVF_vect)        // interrupt service routine
{
	TCNT1 = timer1_counter;   // preload timer

	timercount++;
	if(timercount == 9)
	{
		digitalWrite( LED_PIN, digitalRead(LED_PIN) ^ 1); // Change state of LED
	}
	else
	if(timercount == 10)
	{
		digitalWrite(LED_PIN, digitalRead(LED_PIN) ^ 1); // Change state of LED
		timercount = 0;
	}
}

void setup() {
	FastLED.addLeds< WS2812B, DATA_PIN, COLOR_ORDER>((CRGB *) Leds, ROWS * COLUMNS);
	FastLED.setBrightness(BRIGHTNESS);
	Serial.begin(19200);
	initMap();
}

void rotate(int direction, int column) {
	int number;
	CRGB temp;

	if (direction < 0) {
		CRGB color = Leds[MAP(column, 0)];
		for (int r = ROWS - 1; r > 0; r--) {
			number = MAP(column, r);
			temp = Leds[number];
			Leds[number] = color;
			color = temp;
		}
		Leds[ MAP(column, 0) ] = temp;
	} else {
		CRGB color = Leds[ MAP(column, ROWS-1) ];
		for (int r = 0; r < ROWS; r++) {
			number = MAP(column, r);
			temp = Leds[number];
			Leds[number] = color;
			color = temp;
		}
	}
}

void shift(int direction, int row) {
	int number;
	CRGB temp;

	if (direction < 0) {
		CRGB color = Leds[MAP(0, row)];
		for (int c = COLUMNS - 1; c > 0; c--) {
			number = MAP(c, row);
			temp = Leds[number];
			Leds[number] = color;
			color = temp;
		}
		Leds[MAP(0, row)] = temp;
	} else {
		CRGB color = Leds[MAP(COLUMNS-1, row)];
		for (int c = 0; c < COLUMNS; c++) {
			number = MAP(c, row);
			temp = Leds[number];
			Leds[number] = color;
			color = temp;
		}
	}
}

void test(void)
{
	int number;
	FastLED.clear();
	CRGB color = CRGB::Green;

	for (int c = 0; c < COLUMNS; c++)
	{
		for (int r = 0; r < ROWS; r++)
		{
			number = MAP(c, r);
			Leds[number] = color;
			FastLED.delay(60);
			FastLED.show();
		}
	}
}

void rotate_test(void) {
	FastLED.clear();
	for (int c = 0; c < COLUMNS; c++) {
		Leds[ MAP(c, 0) ] = CRGB::Red;
		Leds[ MAP(c, 1) ] = CRGB::White;
		Leds[ MAP(c, 2) ] = CRGB::Blue;
		Leds[ MAP(c, ROWS-1) ] = CRGB::Green;
	}
	FastLED.show();
	FastLED.delay(120);

	for (int r = 0; r < ROWS; r++)
	{
		rotate( RIGHT, 0 );
		rotate( LEFT,  1 );
		rotate( RIGHT, 2 );
		FastLED.show();
		FastLED.delay(120);
	}

}

void shift_test(void) {
	int number;
	FastLED.clear();

	for (int r = 0; r < ROWS - 3; r += 3) {
		Leds[ MAP(0, r   ) ] = CRGB::Green;
		Leds[ MAP(0, r+1 ) ] = CRGB::Red;
		Leds[ MAP(0, r+2 ) ] = CRGB::Blue;
	}
	FastLED.show();
	FastLED.delay(30);

	for (int c = 0; c < COLUMNS; c++) {
		for (int r = 0; r < ROWS; r++)
		{
			shift( DOWN, r );
			FastLED.show();
			FastLED.delay(30);
		}
	}
}

typedef struct {
	void (*func)(void);
	int times;
} Patterns;

#define MAX_PATTERNS 1
const Patterns PATTERN[] = {
		test, 			   1,
//		rotate_test,       1,
//		shift_test,		   1
};

void loop() {
	FastLED.clear();
	for (int i = 0; i < MAX_PATTERNS; i++) {
		int times = PATTERN[i].times;
		while (times--)
			PATTERN[i].func();
	}
}

