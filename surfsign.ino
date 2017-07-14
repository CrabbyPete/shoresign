// Do not remove the include below
#include "patterns.h"
#include <FastLED.h>

#define DATA_PIN    6
#define LED_PIN     13
#define BRIGHTNESS  100

#define LED_TYPE    WS2812B
#define COLOR_ORDER RGB

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
int LedMap[ COLUMNS * ROWS ];

#define MAP( c, r ) LedMap[c * ROWS + r]


int ledMap(int col, int row) {
	int number = row * 3;

	// Middle strings
	if (col == 1)
		number += 1;

	// Outside strings
	else {
		// If its a horizontal row
		if ((row < HORIZONTAL)
				|| (row >= HORIZONTAL + VERTICAL && row < ROWS - VERTICAL)) 
		{
			// Is it the odd led on the outside string
			if (row % 2) {
				if (col == 0)
					number += 2;
			}
			// Is it the even string on the inside string
			else {
				if (col == 2)
					number += 2;
			}
		}

		// If its a vertical row switch the pattern
		else {
			// Is it the odd row on the outside string
			if (row % 2 ) {
				if (col == 2)
					number += 2;
			}
			// Is it the even row on the inside string
			else {
				if (col == 0)
					number += 2;
			}
		}
	}
	return number;
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
	int n, i = 0;
	for (int c = 0; c < COLUMNS; c++)
		for (int r = 0; r < ROWS; r++) {
			n = ledMap( c, r );
			Serial.print( i );
			Serial.print(',');
			Serial.print( n );
			Serial.print('\n');
			LedMap[i] = n;
			i++;
		}
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

void test(void) {
	int number;
	FastLED.clear();
	CRGB color = CRGB::Green;
	for (int c = 0; c < COLUMNS; c++)
		for (int r = 0; r < ROWS; r++) {
			number = MAP(c, r);
			Leds[number] = color;
			FastLED.delay(60);
			FastLED.show();
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
//		test, 			   1,
//		rotate_test,       1,
		shift_test,		   1
};

void loop() {
	FastLED.clear();
	for (int i = 0; i < MAX_PATTERNS; i++) {
		int times = PATTERN[i].times;
		while (times--)
			PATTERN[i].func();
	}
}

