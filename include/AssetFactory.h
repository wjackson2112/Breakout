#ifndef ASSET_FACTORY_H
#define ASSET_FACTORY_H

#include <string>
#include <unordered_map>
#include <iostream>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Sound.h"
#include "Options.h"

#include "SimpleIni.h"

using namespace std;

class AssetFactory {	
private:
	unordered_map<string, SDL_Texture*> textures;
	unordered_map<string, Sound*> sounds;
	SDL_Renderer* gRenderer;
	Options* options;
public: 
	AssetFactory(SDL_Renderer* gRenderer, Options* options);
	~AssetFactory();
	void printAssets();

	template<typename T>	
	T* getAsset(string key){
		std::cout << "Unsupported type for Asset Factory" << std::endl;
	}

};

#endif