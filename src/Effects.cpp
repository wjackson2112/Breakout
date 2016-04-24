#include "Effects.h"

Effects::Effects(SDL_Texture* texture, EffectsCB alphaCB, EffectsCB colorCB){
	this->texture = texture;

	SDL_GetTextureColorMod(texture, &(this->orig_r), &(this->orig_g), &(this->orig_b));
	SDL_GetTextureAlphaMod(texture, &(this->orig_a));

	this->r = this->orig_r;
	this->g = this->orig_g;
	this->b = this->orig_b;
	this->a = this->orig_a;
	
	this->prevTime = SDL_GetPerformanceCounter();

	this->alphaCB = alphaCB;
	this->colorCB = colorCB;
}

void Effects::apply(){
	Uint64 currTime = SDL_GetPerformanceCounter();
	double timeElapsed = (double) ((currTime - this->prevTime)*1000)/SDL_GetPerformanceFrequency();
	this->prevTime = currTime;

	if(!alphaFrames.empty()){
		if(alphaFrames.front()->frameComplete()){
			alphaFrames.erase(alphaFrames.begin());
			alphaCB();
		}

		alphaFrames.front()->update(timeElapsed, this->a);
	}
	
	SDL_SetTextureAlphaMod(this->texture, this->a);
}

void Effects::reset(){
	colorFrames.clear();
	alphaFrames.clear();
	SDL_SetTextureColorMod(this->texture, this->orig_r, this->orig_g, this->orig_b);
	SDL_SetTextureAlphaMod(this->texture, this->orig_a);
}

void Effects::addColorTransition(Uint32 interval, int r, int g, int b){
	colorFrames.push_back(new ColorKeyFrame(interval, r, g, b));
}

void Effects::addAlphaTransition(Uint32 interval, int start_a, int final_a){
	alphaFrames.push_back(new AlphaKeyFrame(interval, start_a, final_a));
}
