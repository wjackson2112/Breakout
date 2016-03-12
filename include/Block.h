#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <cstdlib>
#include "PhysicsEntity.h"
#include "Ball.h"
#include "TextureFactory.h"

typedef enum
{
	RED,
	ORANGE,
	YELLOW,
	GREEN,
	BLUE,
	PURPLE
} BlockColor;

class Block : public PhysicsEntity
{
private:
	int r, g, b;
	SDL_Texture* texture;
	TextureFactory* textureFactory;
public:
	int width = 80.0;
	int height = 40.0;

	bool visible;

	Block(int x, int y, int width, int height, int* blockCount, TextureFactory* textureFactory, BlockColor color);
	~Block();

	void handleMouseEvents(int mouseState, int x, int y);
	void handleKeyboardEvents(const Uint8*);
	void handleGameEvents(const Uint8* events);
	void update(int frameTime);
	void render(SDL_Renderer*);

	char* type();

	void resolveCollision(PhysicsEntity* collider, PhysicsEntity* object);

	SDL_Point getCenter();
	SDL_Point getOrigin();
	SDL_Point getSize();
	SDL_Point getVelocity();

	bool isDeletable();
};

#endif