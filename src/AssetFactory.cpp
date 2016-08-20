#include "AssetFactory.h"

using namespace std;

AssetFactory::AssetFactory(SDL_Renderer* gRenderer, Options* options){
	this->gRenderer = gRenderer;
	this->options = options;
}

AssetFactory::~AssetFactory(){
	textures.clear();
	sounds.clear();
}

void AssetFactory::printAssets(){
	cout << "Textures" << endl;
	for(auto it = textures.begin(); it != textures.end(); ++it){
		cout << it->first << ":" << (it->second) << " ";
	}
	cout << endl;
}

template<>
SDL_Texture* AssetFactory::getAsset<SDL_Texture>(string key){
	
	//SDL_Surface* surface;
	SDL_Texture* texture;

	unordered_map<string, SDL_Texture *>::iterator it = textures.find(key);

	if(it != textures.end())
	{
		// Uint32 format;
		// int access, w, h;
		
		// SDL_QueryTexture(it->second, &format, &access, &w, &h);
		// texture = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);

		// SDL_SetRenderTarget(gRenderer, texture);
		// SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
		// SDL_SetTextureBlendMode(it->second, SDL_BLENDMODE_BLEND);
		// SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
		// SDL_RenderClear(gRenderer);
		
		// SDL_Rect destRect = {0, 0, w, h};

		// SDL_RenderCopy(gRenderer, it->second, NULL, &destRect);

		// SDL_SetRenderTarget(gRenderer, NULL);
		// SDL_RenderClear(gRenderer);

		// return texture;

		return it->second;
	}

	//surface = IMG_Load(key.c_str());
	texture = IMG_LoadTexture(gRenderer, key.c_str());//SDL_CreateTextureFromSurface( gRenderer, surface );

	textures.insert(make_pair(key, texture));
	return texture;
}

template<>
Sound* AssetFactory::getAsset<Sound>(string key){

	Sound* sound;

	unordered_map<string, Sound*>::iterator it = sounds.find(key);

	if(it != sounds.end())
	{
		return it->second;
	}

	sound = new Sound(key, this->options);

	sounds.insert(make_pair(key, sound));
	return sound;
}