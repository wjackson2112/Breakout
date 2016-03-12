#ifndef ASSET_FACTORY_H
#define ASSET_FACTORY_H

#include <string>
#include <unordered_map>
#include <iostream>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "SimpleIni.h"

using namespace std;

class TextureFactory {	
private:
	unordered_map<string, SDL_Texture*> textures;
	SDL_Renderer* gRenderer;
public: 
	TextureFactory(SDL_Renderer* gRenderer);
	void printTextures();
	SDL_Texture* getTexture(string key);
};

#endif