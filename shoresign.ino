// Do not remove the include below
#include "patterns.h"
#include <FastLED.h>

CRGBPalette16 currentPalette = RainbowColors_p;
TBlendType currentBlending = LINEARBLEND;



#define DATA_PIN    6
#define LED_PIN     13
#define BRIGHTNESS  100

#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB


#define LEFT		-1
#define RIGHT		 1

#define UP			 2
#define DOWN		-2

#define COLUMNS    	 3

#define R1			70
#define R2			69
#define R3			68

#define C1     		13
#define C2     		12
#define C3     		11

#define ROW1 	   166
#define ROW2       162
#define ROW3       158

CRGB Leds[ ROW1 + ROW2 + ROW3 ];
/*
union Map
{
	struct ROWS {
		int outside[166]; // 70-83-153-166 70X13
		int middle [162]; // 69-81-150-162 69X12
		int inside [158]; // 68-79-147-158 68X11
	} Rows;
	int Leds[[ ROW1 + ROW2 + ROW3 ];
} Map = {
*/
#define STRING
#ifndef STRING
const int LedMap[ ROW1 + ROW2 + ROW3 ] =
{
/* 0  1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31   32   33   34   35   36   37   38   39   40   41   42   43   44   45   46   47   48   49   50   51   52   53   54   55   56   57   58   59   60   61   62    63  64   65   66   67   68   69   70   71   72   73   74   75   76   77   78   79   80   81   82   83   84   85   86   87   88   89   90   91   92   93   94   95   96   97   98   99  100  101  102  103  104  105  106  107  108  109  110  111  112  113  114  115  116  117  118  119  120  121  122  123  124  125  126  127  128  129  130  131  132  133  134  135  136  137  138  139  140  141  142  143  144  145  146  147  148  149  150  151  152  153  154  155  156  157  158  159  160  161  162  163  164  165*/
   5, 6, 11, 12, 17, 18, 23, 24, 29, 30, 35, 36, 41, 42, 47, 48, 53, 54, 59, 60, 65, 66, 71, 72, 77, 78, 83, 84, 89, 90, 95, 96, 101, 102, 107, 108, 113, 114, 119, 120, 125, 126, 131, 132, 137, 138, 143, 144, 149, 150, 155, 156, 161, 162, 167, 168, 173, 174, 179, 180, 185, 186, 191, 192, 197, 198, 203, 204, 209, 210, 212, 213, 218, 219, 224, 225, 230, 231, 236, 237, 242, 243, 245, 246, 251, 252, 257, 258, 263, 264, 269, 270, 275, 276, 281, 282, 287, 288, 293, 294, 299, 300, 305, 306, 311, 312, 317, 318, 323, 324, 329, 330, 335, 336, 341, 342, 347, 348, 353, 354, 359, 360, 365, 366, 371, 372, 377, 378, 383, 384, 389, 390, 395, 396, 401, 402, 407, 408, 413, 414, 419, 420, 425, 426, 431, 432, 437, 438, 443, 444, 449, 450, 453, 455, 456, 461, 462, 467, 468, 473, 474, 479, 480, 485,   2,   0,
   4, 7, 10, 13, 16, 19, 22, 25, 28, 31, 34, 37, 40, 43, 46, 49, 52, 55, 58, 61, 64, 67, 70, 73, 76, 79, 82, 85, 88, 91, 94, 97, 100, 103, 106, 109, 112, 115, 118, 121, 124, 127, 130, 133, 136, 139, 142, 145, 148, 151, 154, 157, 160, 163, 166, 169, 172, 175, 178, 181, 184, 187, 190, 193, 196, 199, 202, 205, 208, 211, 214, 217, 220, 223, 226, 229, 232, 235, 238, 241, 244, 247, 250, 253, 256, 259, 262, 265, 268, 271, 274, 277, 280, 283, 286, 289, 292, 295, 298, 301, 304, 307, 310, 313, 316, 319, 322, 325, 328, 331, 334, 337, 340, 343, 346, 349, 352, 355, 358, 361, 364, 367, 370, 373, 376, 379, 382, 385, 388, 391, 394, 397, 400, 403, 406, 409, 412, 415, 418, 421, 424, 427, 430, 433, 436, 439, 442, 445, 448, 451, 454, 457, 460, 463, 466, 469, 472, 475, 478, 481, 484,   1,
   8, 9, 14, 15, 20, 21, 26, 27, 32, 33, 38, 39, 44, 45, 50, 51, 56, 57, 62, 63, 68, 69, 74, 75, 80, 81, 86, 87, 92, 93, 98, 99, 104, 105, 110, 111, 116, 117, 122, 123, 128, 129, 134, 135, 140, 141, 146, 147, 152, 153, 158, 159, 164, 165, 170, 171, 176, 177, 182, 183, 188, 189, 194, 195, 200, 201, 206, 207, 215, 216, 221, 222, 227, 228, 233, 234, 239, 240, 248, 249, 254, 255, 260, 261, 266, 267, 272, 273, 278, 279, 284, 285, 290, 291, 296, 297, 302, 303, 308, 309, 314, 315, 320, 321, 326, 327, 332, 333, 338, 339, 344, 345, 350, 351, 356, 357, 362, 363, 368, 369, 374, 375, 380, 381, 386, 387, 392, 393, 398, 399, 404, 405, 410, 411, 416, 417, 422, 423, 428, 429, 434, 435, 440, 441, 446, 447, 452, 458, 459, 464, 465, 470, 471, 476, 477, 482, 483,   3
};
#else
const int LedMap[ ROW1 + ROW2 + ROW3 ] =
{
/* 0    1    2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19   20   21   22   23   24   25   26   27   28   29   30   31   32   33   34   35   36   37   38   39   40   41   42   43   44   45   46   47   48   49   50   51   52   53   54   55   56   57   58   59   60   61   62   63   64   65   66   67   68   69   70   71   72   73   74   75   76   77   78   79   80   81   82   83   84   85   86   87   88   89   90   91   92   93   94   95   96   97   98   99  100  101  102  103  104  105  106  107  108  109  110  111  112  113  114  115  116  117  118  119  120  121  122  123  124  125  126  127  128  129  130  131  132  133  134  135  136  137  138  139  140  141  142  143  144  145  146  147  148  149  150  151  152  153  154  155  156  157  158  159  160  161  162  163  164  165*/
   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63,  64,  65,  66,  67,  68,  69,  70,  71,  72,  73,  74,  75,  76,  77,  78,  79,  80,  81,  82,  83,  84,  85,  86,  87,  88,  89,  90,  91,  92,  93,  94,  95,  96,  97,  98,  99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165,
 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255, 256, 257, 258, 259, 260, 261, 262, 263, 264, 265, 266, 267, 268, 269, 270, 271, 272, 273, 274, 275, 276, 277, 278, 279, 280, 281, 282, 283, 284, 285, 286, 287, 288, 289, 290, 291, 292, 293, 294, 295, 296, 297, 298, 299, 300, 301, 302, 303, 304, 305, 306, 307, 308, 309, 310, 311, 312, 313, 314, 315, 316, 317, 318, 319, 320, 321, 322, 323, 324, 325, 326, 327,
 328, 329, 330, 331, 332, 333, 334, 335, 336, 337, 338, 339, 340, 341, 342, 343, 344, 345, 346, 347, 348, 349, 350, 351, 352, 353, 354, 355, 356, 357, 358, 359, 360, 361, 362, 363, 364, 365, 366, 367, 368, 369, 370, 371, 372, 373, 374, 375, 376, 377, 378, 379, 380, 381, 382, 383, 384, 385, 386, 387, 388, 389, 390, 391, 392, 393, 394, 395, 396, 397, 398, 399, 400, 401, 402, 403, 404, 405, 406, 407, 408, 409, 410, 411, 412, 413, 414, 415, 416, 417, 418, 419, 420, 421, 422, 423, 424, 425, 426, 427, 428, 429, 430, 431, 432, 433, 434, 435, 436, 437, 438, 439, 440, 441, 442, 443, 444, 445, 446, 447, 448, 449, 450, 451, 452, 453, 454, 455, 456, 457, 458, 459, 460, 461, 462, 463, 464, 465, 466, 467, 468, 469, 470, 471, 472, 473, 474, 475, 476, 477, 478, 479, 480, 481, 482, 483, 484, 485
};
#endif

#define MAP( c, r ) LedMap[ ( c * ROW1 +  r ) - ( c/2 * 4) ]

int XY( int x, int y )
{

	switch( y )
	{

	// Horizontal lines
	case 0:
		if ( x < 3 )
			return MAP( 0, ROW1 - x );

		return MAP( 0, x - 2 );


	case 1:
		if ( x < 3 )
			return MAP( 1, ROW2 - x );

		return MAP( 1, x - 2 );

	case 2:
		if ( x < 3 )
			return MAP( 2, ROW3 - x );

		return MAP( 2, x - 3);

	case 12:
		return MAP( 2, ROW3 - C3 - x + 2 );

	case 13:
		return MAP( 1, ROW2 - C2 - x + 1 );

	case 14:
		return MAP( 0, ROW1 - C1 - x + 1 );

	default:
		y -= 3;
		switch( x )
		{
		case 0:
			return MAP( 0, ROW1 - y - 3 );

		case 1:
			return MAP( 1, ROW2 - y - 2 ); //160

		case 2:
			return MAP( 2, ROW3 - y - 2 ); // 156

		case R1-1:
			return MAP( 2, R3 + y + 1   );

		case R1:
			return MAP( 1, R2 + y + 1   );

		case R1+1:
			return MAP( 0, R1 + y + 2   );

		default:
			return -1;
		}
	}
}


void test(void)
{
	FastLED.clear();

	CRGB color = CRGB::Green;
	for ( int i = 0; i < 486; i++ )
		Leds[i] = color;

	FastLED.show();
	FastLED.delay( 360 );
}


void setup() {
	FastLED.addLeds< WS2812B, DATA_PIN, COLOR_ORDER>((CRGB *) Leds, ROW1+ROW2+ROW3);
	FastLED.setBrightness(BRIGHTNESS);
	test();
	Serial.begin(9600);
}


void rectangle( int column, CRGB color )
{
	int size = ROW1 - column * 4;
	for ( int r = 0; r < size; r++ )
		Leds[ MAP( column, r ) ] = color;
}


void diagonal( int row, CRGB color  )
{
	
	if ( row < 0 )
	{
		Leds[ MAP( 0, ROW1-2 + row ) ] = color;
		Leds[ MAP( 1, ROW2-2 + row ) ] = color;
		Leds[ MAP( 2, ROW3-2 + row ) ] = color;
	}
	else
	{
		Leds[ MAP( 0, row ) ] = color;
		Leds[ MAP( 1, row ) ] = color;
		Leds[ MAP( 2, row ) ] = color;
	}

	if ( row < R3  )
	{
		row = 142 - row;
		if ( row > R3 + C3 + 2 )
		{
			Leds[ MAP( 0, row     ) ] = color;
			Leds[ MAP( 1, row - 2 ) ] = color;
			Leds[ MAP( 2, row - 4 ) ] = color;
		}
	}
	else
	{
		row += 1;
		Leds[ MAP( 0, row + 4 ) ] = color;
		Leds[ MAP( 1, row + 1 ) ] = color;
		//Leds[ MAP( 2, row ) ] = color;
	}
}

void diagonal_test( void )
{
	rectangle( 0, CRGB::OrangeRed);
	rectangle( 1, CRGB::OrangeRed);
	rectangle( 2, CRGB::OrangeRed);
	for ( int i=73; i>0; i-=3 )
	{
		diagonal( i, CRGB::Black);
		FastLED.show();
		FastLED.delay( 60 );
	}
}


void stripes( void )
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
		Leds[ MAP( 0, x-2 + y + 4 )  ]  = colors[c];
		Leds[ MAP( 1, x-2 + y + 2 )   ] = colors[c];
		Leds[ MAP( 2, x-2 + y     )   ] = colors[c];

		FastLED.show();
		FastLED.delay( 30 );

		c++;
		if ( c > 2 )
			c = 0;
	}
}

void rotate(int column, int start, int size )
{
	int number;
	CRGB temp;

	int rows = ROW1 - ( 4 * column );
	int last = ( start + abs(size) - 1 ) % rows;

	// Left to right
	if ( size > 0 )
	{
		CRGB color = Leds[ MAP( column, start ) ];
		for (int r = last; r > start; r--)
		{
			number = MAP(column, r);
			temp = Leds[number];
			Leds[number] = color;
			color = temp;
		}
		Leds[ MAP(column, start) ] = temp;
	}
	// Right to left
	else
	{
		CRGB color = Leds[ MAP(column, start) ];
		for (int r = start; r < last; r++) {
			number = MAP(column, r);
			temp = Leds[number];
			Leds[number] = color;
			color = temp;
		}
		Leds[ MAP(column, start) ] = temp;
	}
}


void rotate_bar( int direction, int bar )
{

	int length = R3+1;
	switch( bar )
	{
	case UP:
		if ( direction == RIGHT )
			length = length * -1;

		rotate( 0, 1, length );
		rotate( 1, 1, length );
		rotate( 2, 0, length );
		break;

	case DOWN:
		if ( direction == LEFT )
			length = length * -1;

		rotate( 0, R1+C1,   length );
		rotate( 1, R2+C2-1, length );
		rotate( 2, R3+C3-1, length );
		break;
	}
}

void rotate_test(void)
{
	CRGB colors[3] = { CRGB::Red, CRGB::White, CRGB::Blue };
	CRGB color;

	int number;

	//FastLED.clear();
	/*
	for ( int x = 3; x < R1+1; x++ )
	{
		color = colors[ (( x -3 ) / 4 ) % 3 ];

		Leds[ XY( x, 0 ) ] = color;
		Leds[ XY( x, 1 ) ] = color;
		Leds[ XY( x, 2 ) ] = color;

		Leds[ XY( x, 12  ) ] = color;
		Leds[ XY( x, 13  ) ] = color;
		Leds[ XY( x, 14  ) ] = color;
	}
	FastLED.show();
	*/
	for ( int y=0; y < C1; y++ )
	{
		color = colors[ ( y / 4 ) % 3 ];
		for ( int x = 0; x < 3 ; x++ )
		{
			Leds[ XY( x, y ) ] = color;
			FastLED.show();
		}
	}

	/*
	FastLED.show();
	for (int r = 0; r < 100; r++)
	{
		rotate_bar( RIGHT, DOWN );
		rotate_bar( LEFT, UP);

		FastLED.show();
		FastLED.delay( 60 );
	}
	*/
}

void flag( void )
{
	int number;

	CRGB color;

	FastLED.clear();

	for ( int y = 0; y < C1+2; y++)
	{
		if ( y % 2 == 0 )
			color = CRGB::Red;
		else
			color = CRGB::White;

		for ( int x = 0; x < R1+2;  x++ )
		{
			number = XY(  x, y );
			if ( number < 0 )
				continue;
			Leds[ number ] = color;
		}
		FastLED.show();
		FastLED.delay( 30 );
	}

	for ( int x = R1 + 2; x >= 0; x-- )
	{
		if ( x % 5  == 0  && x > 0 && x < R1+1 )
			color = CRGB::White;
		else
			color = CRGB::DarkBlue;

		for ( int y = 0; y < C1 + 2; y ++ )
		{
			number = XY( x, y );
			if ( number < 0 )
				continue;
			Leds[ number ] = color;
		}
		FastLED.show();
		FastLED.delay( 30 );
	}

	for( int i = 0; i < R1; i++ )
	{

		rotate_bar( LEFT, DOWN );
		rotate_bar( LEFT, UP    );

		FastLED.show();
		FastLED.delay( 60 );
	}
}

void italy(void) {
	FastLED.clear();

	CRGB colors[6] = { CRGB::Red,       CRGB::White,      CRGB::Blue,
				       CRGB::DarkGreen, CRGB::White,      CRGB::Red };

	for ( int c = 0; c < 20; c++ )
		for( int i=0; i<4; i++ )
		{
			rectangle(0, colors[i]  );
			rectangle(1, colors[i+1]);
			rectangle(2, colors[i+2]);
			FastLED.show();
			FastLED.delay(60);
		}
}

void palette( void )
{
	int colorIndex = 0;
	for( int i = 0; i < ROW1+ROW2+ROW3; i++)
	{
		Leds[i] = ColorFromPalette( currentPalette, colorIndex, BRIGHTNESS, currentBlending);
		colorIndex += 3;
	}
	FastLED.show();
	FastLED.delay( 3600 );
	for ( int i=0; i< 500; i++)
	{
		rotate( 0, 0, ROW1-1 );
		rotate( 1, 0, ROW2-1 );
		rotate( 2, 0, ROW3-1 );
		FastLED.show();
	}
}

typedef struct {
	void (*func)(void);
	int times;
} Patterns;

#define MAX_PATTERNS 1
const Patterns PATTERN[MAX_PATTERNS] = {
//		palette,      1,
//		flag,         1,
//		diagonal_test,1,
		rotate_test,  1,
//		italy,        1
};

void loop()
{
	for (int i = 0; i < MAX_PATTERNS; i++)
	{
		int times = PATTERN[i].times;
		while (times--)
			PATTERN[i].func();
	}

}

