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

	cout << "Sounds" << endl;
	for(auto it = sounds.begin(); it != sounds.end(); ++it){
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

	textures.insert( make_pair(key, texture) );
	return texture;
}