// Do not remove the include below
#include "patterns.h"
#include <FastLED.h>

#define DATA_PIN    6
#define BRIGHTNESS  100

#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB

// This is the size of the test platform
#ifdef TEST
#define COLUMNS    	3
#define ROWS 	    64

#define HORIZONTAL  22
#define VERTICAL    10

#else
#define COLUMNS    	3
#define ROWS 	    162

#define HORIZONTAL  70
#define VERTICAL    11
#endif


#define LEFT		-1
#define RIGHT		1

#define UP			1
#define DOWN		-1

CRGB Leds[ COLUMNS * ROWS ];
int Map[ COLUMNS * ROWS ];

#define MAP( c, r ) Map[c * ROWS + r]

int ledMap( int col, int row )
{
	int number = row * 3;

	// Middle strings
	if ( col ==  1)
		number += 1;

	// Outside strings
	else
	{
		// If its a horizontal row
		if ( ( row < HORIZONTAL) || ( row >= HORIZONTAL + VERTICAL  && row < ROWS - VERTICAL) )
		{
			// Is it the odd led on the outside string
			if ( row % 2 )
			{
				if ( col == 0 )
					number += 2;
			}
			// Is it the even string on the inside string
			else
			{
	            if ( col == 2 )
	            	number += 2;
			}
		}

		// If its a vertical row switch the pattern
		else
		{
			if ( row % 2 != 0 )
			{
				if ( col == 0 )
					number += 2;
			}
	        else
	        {
	        	if ( col == 2 )
	        		number += 2;
	        }
		}
	}
	return number;
}


void initMap( void )
{
	int i = 0;
	for ( int c = 0; c < COLUMNS; c++)
		for ( int r = 0; r < ROWS; r++ )
			Map[i++] = MAP( c, r );
}

void setup()
{
    FastLED.addLeds<NEOPIXEL,DATA_PIN>( (CRGB *)Leds, ROWS*COLUMNS );
    FastLED.setBrightness(BRIGHTNESS);
    initMap();
    Serial.begin(9600);
}


void rotate( int direction, int column )
{
	int number;
	CRGB temp;

	if ( direction < 0 )
	{
		CRGB color = Leds[ MAP( column, 0) ];
		for(int r=ROWS-1; r > 0; r-- )
		{
			number = MAP( column, r );
			temp = Leds[number];
			Leds[number] = color;
			color = temp;
		}
		Leds[MAP(column,0)] = temp;
	}
	else
	{
		CRGB color = Leds[ MAP( column, ROWS-1 ) ];
		for( int r=0; r<ROWS; r++ )
		{
			number = MAP( column, r );
			temp = Leds[ number ];
			Leds[ number ] = color;
			color = temp;
		}
	}
}

void shift( int direction, int row )
{
	int number;
	CRGB temp;

	if ( direction < 0 )
	{
		CRGB color = Leds[ MAP( 0, row ) ];
		for(int c=COLUMNS-1; c > 0; c-- )
		{
			number = MAP( c, row );
			temp = Leds[number];
			Leds[number] = color;
			color = temp;
		}
		Leds[MAP(0,row)] = temp;
	}
	else
	{
		CRGB color = Leds[ MAP( COLUMNS-1, row ) ];
		for( int c=0; c<COLUMNS; c++ )
		{
			number = MAP( c, row );
			temp = Leds[ number ];
			Leds[ number ] = color;
			color = temp;
		}
	}
}


void test( void )
{
	int number;
	FastLED.clear();
	CRGB color = CRGB::Green;
	for ( int c=0; c<COLUMNS; c++)
		for ( int r=0; r<ROWS; r++)
		{
			number = MAP( c, r );
			Leds[ number ] = color;
			FastLED.delay(300);
			FastLED.show();
		}
}


void rotate_test( void )
{
	FastLED.clear();
	for( int c=0; c<COLUMNS; c++ )
	{
		Leds[ MAP(c,0) ] = CRGB::Red;
		Leds[ MAP(c,1) ] = CRGB::White;
		Leds[ MAP(c,2) ] = CRGB::Blue;
		Leds[ MAP(c,ROWS-1) ] = CRGB::Green;
	}
	FastLED.show();

	for ( int r=0; r<ROWS; r++)
	{
		rotate( RIGHT, 0);
		rotate( RIGHT, 1);
		rotate( RIGHT, 2);
		FastLED.show();
		FastLED.delay(30);
	}
}

void shift_test( void )
{
	int number;
	FastLED.clear();

	for( int r=0; r<ROWS-3; r+= 3)
	{
		number = r + 1;
		Leds[ MAP(0, r) ]        = CRGB::Green;
		Leds[ MAP(0, number) ]   = CRGB::Red;
	}
	FastLED.show();

	for ( int c=0; c<COLUMNS; c++)
	{
		for( int r=0; r<ROWS; r++ )
		{
			shift( UP, r );
			FastLED.show();
		}
	}
}

typedef struct
{
    void (*func)(void);
    int times;
} Patterns;


#define MAX_PATTERNS 1
const Patterns PATTERN[]= {
		test, 			   1,
//		rotate_test,       1,
//		shift_test,		   1
};

void loop()
{
	for (int i=0; i< MAX_PATTERNS; i++)
	{
		int times = PATTERN[i].times;
		while ( times-- )
			PATTERN[i].func();
	}
}

