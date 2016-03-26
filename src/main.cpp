//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include "ProgramManager.h"
#include "Globals.h"
#include "SimpleIni.h"
#include "AssetFactory.h"
#include <memory>

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;


CSimpleIniA ini;

bool init();
void quitEventReceived();
void close();

void load_settings()
{	
	const char * val;

	ini.SetUnicode();
	ini.LoadFile("breakout.ini");
	
	val = ini.GetValue("dimensions", "width", std::to_string(DEF_SCREEN_WIDTH).c_str());
	Globals::screenWidth=atoi(val);
	ini.SetValue("dimensions", "width", std::to_string(Globals::screenWidth).c_str());

	val = ini.GetValue("dimensions", "height", std::to_string(DEF_SCREEN_HEIGHT).c_str());
	Globals::screenHeight=atoi(val);
	ini.SetValue("dimensions", "height", std::to_string(Globals::screenHeight).c_str());

	val = ini.GetValue("dimensions", "fullScreen", std::to_string(DEF_FULL_SCREEN).c_str());
	Globals::fullScreen=atoi(val);
	ini.SetValue("dimensions", "fullScreen", std::to_string(Globals::fullScreen).c_str());

	Globals::fieldRatio = (float) 3/ (float) 4;
	Globals::fieldWidth = (Globals::screenHeight * Globals::fieldRatio) / 10 * 10;
	Globals::fieldHeight = Globals::screenHeight;
	Globals::xOffset = (Globals::screenWidth / 2) - (Globals::fieldWidth / 2);
	Globals::yOffset = 0;

	Globals::blockWidth = Globals::fieldWidth / 10;
	Globals::blockHeight = Globals::blockWidth * 2/3;
	Globals::paddleWidth = Globals::blockWidth;
	Globals::paddleHeight = Globals::blockHeight / 2;
	Globals::ballWidth = Globals::blockHeight / 2;
	Globals::ballHeight = Globals::blockHeight / 2;


}

bool init()
{
	//Init SDL
	if(SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	//Init SDL_image
	int imgFlags = IMG_INIT_PNG;
	if(!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return false;
	}

	//Init Fonts
	if(TTF_Init() < 0)
	{
		printf("Font library could not intiialize! SDL_Error: %s\n", TTF_GetError());
		return false;
	}

	load_settings();

	//Create Window
	gWindow = SDL_CreateWindow("Breakout", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Globals::screenWidth, Globals::screenHeight, SDL_WINDOW_SHOWN);
	if(gWindow == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	if(Globals::fullScreen){
		SDL_SetWindowFullscreen(gWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
	}
	//Create Renderer
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);
	if(gRenderer == NULL)
	{
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	return true;
}

void close()
{
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;

	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	init();

	SDL_RenderPresent(gRenderer);

	ProgramManager* manager = new ProgramManager(gRenderer);
	manager->loop();
	delete manager;

	close();

	return 0;
}