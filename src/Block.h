#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <cstdlib>
#include "Entity.h"
#include "Ball.h"

class Block : public Entity
{
private:
	int r, g, b;
	int* blockCount;
public:
	int width = 40.0;
	int height = 40.0;

	bool visible;

	Block(int x, int y, int* blockCount);
	~Block();

	void handleEvents(const Uint8*);
	void update(int frameTime);
	void render(SDL_Renderer*);
	void resolveCollision(Entity*);

	SDL_Point getCenter();
	SDL_Point getOrigin();
	SDL_Point getSize();
	SDL_Point getVelocity();

	bool isDeletable();
};

#endif