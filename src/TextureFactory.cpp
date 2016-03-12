#include "TextureFactory.h"

using namespace std;

TextureFactory::TextureFactory(SDL_Renderer* gRenderer){
	this->gRenderer = gRenderer;
}

void TextureFactory::printTextures(){
	for(auto it = textures.begin(); it != textures.end(); ++it){
		cout << it->first << ":" << (it->second) << " ";
	}

	cout << endl;
}

SDL_Texture* TextureFactory::getTexture(string key){
	
	SDL_Surface* surface;
	SDL_Texture* texture;

	unordered_map<string, SDL_Texture *>::iterator it = textures.find(key);

	if(it != textures.end())
	{
		return it->second;
	}

	surface = IMG_Load(key.c_str());
	texture = SDL_CreateTextureFromSurface( gRenderer, surface );

	textures.insert( make_pair(key, texture) );
	return texture;
}