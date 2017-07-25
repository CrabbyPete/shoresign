// Do not remove the include below
#include "patterns.h"
#include <FastLED.h>

#define DATA_PIN    6
#define LED_PIN     13
#define BRIGHTNESS  10

#define LED_TYPE    WS2812B
#define COLOR_ORDER RGB


#define LEFT		-1
#define RIGHT		 1

#define UP			 1
#define DOWN		-1

#define COLUMNS    	3
#define ROW1 	    166
#define ROW2        162
#define ROW3        158

CRGB Leds[ ROW1 + ROW2 + ROW3 ];
/*
union Map
{
	struct ROWS {
		int outside[166]; // 5-70-83-155-166 70X13
		int middle [162]; // 4-69-81-152-163 69X12
		int inside [158]; // 9-68-80-150-158 68X11
	} Rows;
	int Leds[[ ROW1 + ROW2 + ROW3 ];
} Map = {
*/
int LedMap[ ROW1 + ROW2 + ROW3 ] =
{
/* 0  1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31   32   33   34   35   36   37   38   39   40   41   42   43   44   45   46   47   48   49   50   51   52   53   54   55   56   57   58   59   60   61   62    63  64   65   66   67   68   69   70   71   72   73   74   75   76   77   78   79   80   81   82   83   84   85   86   87   88   89   90   91   92   93   94   95   96   97   98   99  100  101  102  103  104  105  106  107  108  109  110  111  112  113  114  115  116  117  118  119  120  121  122  123  124  125  126  127  128  129  130  131  132  133  134  135  136  137  138  139  140  141  142  143  144  145  146  147  148  149  150  151  152  153  154  155  156  157  158  159  160  161  162  163  164  165*/
   5, 6, 11, 12, 17, 18, 23, 24, 29, 30, 35, 36, 41, 42, 47, 48, 53, 54, 59, 60, 65, 66, 71, 72, 77, 78, 83, 84, 89, 90, 95, 96, 101, 102, 107, 108, 113, 114, 119, 120, 125, 126, 131, 132, 137, 138, 143, 144, 149, 150, 155, 156, 161, 162, 167, 168, 173, 174, 179, 180, 185, 186, 191, 192, 197, 198, 203, 204, 209, 210, 212, 213, 218, 219, 224, 225, 230, 231, 236, 237, 242, 243, 245, 246, 251, 252, 257, 258, 263, 264, 269, 270, 275, 276, 281, 282, 287, 288, 293, 294, 299, 300, 305, 306, 311, 312, 317, 318, 323, 324, 329, 330, 335, 336, 341, 342, 347, 348, 353, 354, 359, 360, 365, 366, 371, 372, 377, 378, 383, 384, 389, 390, 395, 396, 401, 402, 407, 408, 413, 414, 419, 420, 425, 426, 431, 432, 437, 438, 443, 444, 449, 450, 453, 455, 456, 461, 462, 467, 468, 473, 474, 479, 480, 485,   2,   0,
   4, 7, 10, 13, 16, 19, 22, 25, 28, 31, 34, 37, 40, 43, 46, 49, 52, 55, 58, 61, 64, 67, 70, 73, 76, 79, 82, 85, 88, 91, 94, 97, 100, 103, 106, 109, 112, 115, 118, 121, 124, 127, 130, 133, 136, 139, 142, 145, 148, 151, 154, 157, 160, 163, 166, 169, 172, 175, 178, 181, 184, 187, 190, 193, 196, 199, 202, 205, 208, 211, 214, 217, 220, 223, 226, 229, 232, 235, 238, 241, 244, 247, 250, 253, 256, 259, 262, 265, 268, 271, 274, 277, 280, 283, 286, 289, 292, 295, 298, 301, 304, 307, 310, 313, 316, 319, 322, 325, 328, 331, 334, 337, 340, 343, 346, 349, 352, 355, 358, 361, 364, 367, 370, 373, 376, 379, 382, 385, 388, 391, 394, 397, 400, 403, 406, 409, 412, 415, 418, 421, 424, 427, 430, 433, 436, 439, 442, 445, 448, 451, 454, 457, 460, 463, 466, 469, 472, 475, 478, 481, 484,   1,
   8, 9, 14, 15, 20, 21, 26, 27, 32, 33, 38, 39, 44, 45, 50, 51, 56, 57, 62, 63, 68, 69, 74, 75, 80, 81, 86, 87, 92, 93, 98, 99, 104, 105, 110, 111, 116, 117, 122, 123, 128, 129, 134, 135, 140, 141, 146, 147, 152, 153, 158, 159, 164, 165, 170, 171, 176, 177, 182, 183, 188, 189, 194, 195, 200, 201, 206, 207, 215, 216, 221, 222, 227, 228, 233, 234, 239, 240, 248, 249, 254, 255, 260, 261, 266, 267, 272, 273, 278, 279, 284, 285, 290, 291, 296, 297, 302, 303, 308, 309, 314, 315, 320, 321, 326, 327, 332, 333, 338, 339, 344, 345, 350, 351, 356, 357, 362, 363, 368, 369, 374, 375, 380, 381, 386, 387, 392, 393, 398, 399, 404, 405, 410, 411, 416, 417, 422, 423, 428, 429, 434, 435, 440, 441, 446, 447, 452, 458, 459, 464, 465, 470, 471, 476, 477, 482, 483,   3
};


#define MAP( c, r ) LedMap[ ( c * 166   +  r ) - ( c/2 * 4) ]



#ifdef STRING
void initMap(void)
{
	for ( int i=0; i< sizeof( LedMap ); i++ )
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
	FastLED.addLeds< WS2812B, DATA_PIN, COLOR_ORDER>((CRGB *) Leds, ROW1+ROW2+ROW3);
	FastLED.setBrightness(BRIGHTNESS);
	Serial.begin(19200);
	initMap();
}

void rectangle( int column, CRGB color )
{
	int size;
	if ( column == 0 )
		size = 166;
	else
	 	size = column * 166 - ( column * 4 );

	for ( int r = 0; r < size; r++ )
	{
		Leds[ MAP( column, r ) ] = color;
	}
}

void vertical( int row, CRGB color )
{
	int size = 6;

	if ( row < 3 && row > 67 )
	{
		switch( row )
		{
			case 0:
			case 68:
				size = 13;
				break;
			case 2:
			case 69:
				size = 12;
				break;
			case 3:
			case 70:
				size = 13;
		}
	}

	for ( int y = 0; y < size; y ++ )
	{
		Leds[ MAP( y, row ) ] = color;
	}

}

void diagonal( void )
{
	FastLED.clear();

	int x, y, c = 0;
	const CRGB colors[3] = { CRGB::Red, CRGB::White, CRGB::Blue };

	for ( x = 69, y = 0; x > 1; x-=3 )
	{

		Leds[ MAP( 0, x )    ] = colors[c];
		Leds[ MAP( 1, x )    ] = colors[c];
		Leds[ MAP( 2, x )    ] = colors[c];

		Leds[ MAP( 0, x-1 )  ] = colors[c];
		Leds[ MAP( 1, x-1 )  ] = colors[c];
		Leds[ MAP( 2, x-1 )  ] = colors[c];

		Leds[ MAP( 0, x-2 )  ] = colors[c];
		Leds[ MAP( 1, x-2 )  ] = colors[c];
		Leds[ MAP( 2, x-2 )  ] = colors[c];


		y += 2;
		Leds[ MAP( 0, x + y + 4 )  ] = colors[c];
		Leds[ MAP( 1, x + y + 2 )  ] = colors[c];
		Leds[ MAP( 2, x + y     )  ] = colors[c];

		y += 2;
		Leds[ MAP( 0, x-1  + y + 4 )  ] = colors[c];
		Leds[ MAP( 1, x-1  + y + 2 )  ] = colors[c];
		Leds[ MAP( 2, x-1  + y     )  ] = colors[c];


		y += 2;
		Leds[ MAP( 0, x-2 + y + 4 )  ] = colors[c];
		Leds[ MAP( 1, x-2 + y + 2 )   ] = colors[c];
		Leds[ MAP( 2, x-2 + y     )   ] = colors[c];

		FastLED.show();
		FastLED.delay( 30 );

		c++;
		if ( c > 2 )
			c = 0;

	}

}

/*
void draw( int x0, int y0, int x1, int y1, CRGB color )
{

}
*/
void rotate(int direction, int column) {
	int number;
	CRGB temp;

	int rows = 166 - ( 4 * column );

	if (direction < 0) {
		CRGB color = Leds[MAP(column, 0)];
		for (int r = rows - 1; r > 0; r--) {
			number = MAP(column, r);
			temp = Leds[number];
			Leds[number] = color;
			color = temp;
		}
		Leds[ MAP(column, 0) ] = temp;
	} else {
		CRGB color = Leds[ MAP(column, rows-1) ];
		for (int r = 0; r < rows; r++) {
			number = MAP(column, r);
			temp = Leds[number];
			Leds[number] = color;
			color = temp;
		}
	}
}

void shift(int direction, int row ) {
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
	/*
	for (int c = 0; c < COLUMNS; c++)
	{

		int rows = 166 - ( 2 * c );
		Serial.println( rows );
		for (int r = 0; r < rows; r++)
		{
			number = MAP(c, r);
			//Serial.println( number );

			Leds[number] = color;
			FastLED.delay(10);
			FastLED.show();
		}
	}
	*/
	for ( int r = 0; r < 168; r++ )
	{
		FastLED.clear();
		Leds[ MAP( 0, r ) ] = CRGB::Green;
		Leds[ MAP( 1, r ) ] = CRGB::Green;
		Leds[ MAP( 2, r ) ] = CRGB::Green;
		FastLED.show();
		FastLED.delay( 360 );
	}
}

void rotate_test(void) {
	FastLED.clear();
	for (int c = 0; c < COLUMNS; c++) {
		Leds[ MAP(c, 0) ] = CRGB::Red;
		Leds[ MAP(c, 1) ] = CRGB::White;
		Leds[ MAP(c, 2) ] = CRGB::Blue;
	}
	FastLED.show();
	FastLED.delay(360);

	for (int r = 0; r < ROW3; r++)
	{
		rotate( RIGHT, 0 );
		rotate( LEFT,  1 );
		rotate( RIGHT, 2 );

		FastLED.show();
		FastLED.delay(120);
	}

}

void shift_test(void) {
	FastLED.clear();

	rectangle(0, CRGB::Red);
	rectangle(1, CRGB::White);
	rectangle(2, CRGB::Blue);

	FastLED.show();
	FastLED.delay(2000);

	for (int c = 0; c < COLUMNS; c++) {
		for (int r = 0; r < ROW3; r++)
		{
			shift( DOWN, r );
			FastLED.show();
			FastLED.delay(360);
		}
	}
}

typedef struct {
	void (*func)(void);
	int times;
} Patterns;

#define MAX_PATTERNS 1
const Patterns PATTERN[MAX_PATTERNS] = {
//		test, 			   1,
//		rotate_test,       1,
//		shift_test,		   1,
		diagonal,          1,
};

void loop() {
	FastLED.clear();
	for (int i = 0; i < MAX_PATTERNS; i++) {
		int times = PATTERN[i].times;
		while (times--)
			PATTERN[i].func();
	}
}

