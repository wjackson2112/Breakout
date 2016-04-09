#ifndef EFFECTS_H
#define EFFECTS_H

#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include <functional>

using namespace std;

class Effects
{

public:
	//using EffectsCB = void (*)();
	typedef std::function<void(void)> EffectsCB;

private:
	class ColorKeyFrame
	{
	private:
		Uint8 r, g, b;
		Uint8 start_r, start_g, start_b;
		
		Uint64 transitionTime, elapsedTime;
	public:
		ColorKeyFrame(Uint32 completionTime, int r, int g, int b){
			this->r = r;
			this->g = g;
			this->b = b;
			this->elapsedTime = 0;
			this->transitionTime = completionTime / 1000 * SDL_GetPerformanceFrequency();
		}

		void update(Uint64 elapsedTime, Uint8& r, Uint8& g, Uint8& b){
			
			this->elapsedTime += elapsedTime;

			if(elapsedTime >= transitionTime)
			{
				elapsedTime = transitionTime;
			}

			r = (this->r - this->start_r)/(elapsedTime/transitionTime) + this->start_r;
			g = (this->g - this->start_g)/(elapsedTime/transitionTime) + this->start_g;
			b = (this->b - this->start_b)/(elapsedTime/transitionTime) + this->start_b;
		}

		bool frameComplete()
		{
			if(this->elapsedTime != this->transitionTime){
				return false;
			}
			return true;
		}
	};

	class AlphaKeyFrame
	{
		Uint8 final_a;
		Uint8 start_a;
		
		double transitionTime, elapsedTime;
	public:
		AlphaKeyFrame(Uint64 transitionTime, int start_a, int final_a)
		{
			this->start_a = start_a;
			this->final_a = final_a;
			this->elapsedTime = 0;
			this->transitionTime = transitionTime;
		}

		void update(double elapsedTime, Uint8& a){
			
			this->elapsedTime += elapsedTime;

			if(this->elapsedTime >= this->transitionTime)
			{
				this->elapsedTime = this->transitionTime;
				a = this->final_a;
				return;
			}

			a = ((this->start_a - this->final_a) * (1 - (this->elapsedTime/this->transitionTime))) + this->start_a;
		}

		bool frameComplete()
		{
			if(this->elapsedTime != this->transitionTime){
				return false;
			}
			return true;
		}
	};

	SDL_Texture* texture;
	SDL_TimerID frameTimer;
	Uint64 prevTime;
	vector<ColorKeyFrame*> colorFrames;
	vector<AlphaKeyFrame*> alphaFrames;

	EffectsCB alphaCB, colorCB;

	Uint8 r, g, b, a;
	Uint8 orig_r, orig_g, orig_b, orig_a;

public:
	Effects(SDL_Texture* texture, EffectsCB alphaCB, EffectsCB colorCB);
	void apply();
	void reset();
	void addColorTransition(Uint32 interval, int r, int g, int b);
	void addAlphaTransition(Uint32 interval, int start_a, int final_a);
};

#endif