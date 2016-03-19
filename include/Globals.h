#ifndef GLOBALS_H
#define GLOBALS_H

namespace Globals
{
	extern int screenWidth;
	extern int screenHeight;
	extern float fieldRatio;
	extern int fieldWidth;
	extern int fieldHeight;
	extern int xOffset;
	extern int yOffset;
	extern int blockWidth;
	extern int blockHeight;
	extern int paddleWidth;
	extern int paddleHeight;
	extern int ballWidth;
	extern int ballHeight;
	extern int fullScreen;
}

#endif

#define DEF_SCREEN_WIDTH 	1024
#define DEF_SCREEN_HEIGHT 	768
#define DEF_FULL_SCREEN 	0
// #define FIELD_RATIO 	3 / 4

// #if SCREEN_WIDTH > SCREEN_HEIGHT

// #define FIELD_WIDTH  	(SCREEN_HEIGHT * FIELD_RATIO) / 10 * 10
// #define FIELD_HEIGHT 	SCREEN_HEIGHT
// #define X_OFFSET		(SCREEN_WIDTH / 2)  - (FIELD_WIDTH / 2)
// #define Y_OFFSET		0 

// #endif

// #define BLOCK_WIDTH 	FIELD_WIDTH / 10
// #define BLOCK_HEIGHT	BLOCK_WIDTH * 2/3