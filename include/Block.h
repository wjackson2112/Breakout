#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <cstdlib>
#include "PhysicsEntity.h"
#include "Ball.h"
#include "IBlockDelegate.h"

class Block : public PhysicsEntity
{
private:
	int r, g, b;
	IBlockDelegate* delegate;
public:
	int width = 40.0;
	int height = 40.0;

	bool visible;

	Block(int x, int y, int* blockCount, IBlockDelegate* delegate);
	~Block();

	void setDelegate(IBlockDelegate* delegate);

	void handleEvents(const Uint8*);
	void update(int frameTime);
	void render(SDL_Renderer*);
	void resolveCollision(PhysicsEntity*);

	Block* clone() const;
	Block* collisionClone() const;

	SDL_Point getCenter();
	SDL_Point getOrigin();
	SDL_Point getSize();
	SDL_Point getVelocity();

	bool isDeletable();
};

#endif