#include "AssetFactory.h"

using namespace std;

AssetFactory::AssetFactory(SDL_Renderer* gRenderer){
	this->gRenderer = gRenderer;
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
	
	SDL_Surface* surface;
	SDL_Texture* texture;

	unordered_map<string, SDL_Texture *>::iterator it = textures.find(key);

	if(it != textures.end())
	{
		return it->second;
	}

	surface = IMG_Load(key.c_str());
	texture = SDL_CreateTextureFromSurface( gRenderer, surface );

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

	sound = new Sound(key);

	sounds.insert(make_pair(key, sound));
	return sound;
}