#ifndef GLOBALS_H
#define GLOBALS_H

#include "SimpleIni.h"

namespace Globals
{
	extern CSimpleIniA ini;

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

	extern int mainMenuX;
	extern int mainMenuY;
	extern int mainMenuRowPadding;
	extern int mainMenuColPadding;
	extern int mainMenuRowHeight;
	extern int mainMenuColWidth;

	extern int pauseMenuX;
	extern int pauseMenuY;
	extern int pauseMenuRowPadding;
	extern int pauseMenuColPadding;
	extern int pauseMenuRowHeight;
	extern int pauseMenuColWidth;
}

#endif