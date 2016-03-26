#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <cstdlib>
#include "PhysicsEntity.h"
#include "Ball.h"
#include "AssetFactory.h"
#include "StateMachine.h"

typedef enum
{
	IDLE_ST,
	FADING_ST,
	GONE_ST
} BlockState;

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
	StateMachine<BlockState>* state;
	SDL_Texture* texture;
	AssetFactory* assetFactory;

	void stateChanged(BlockState prevState, BlockState currState);

public:
	int width = 80.0;
	int height = 40.0;

	Block(int x, int y, int width, int height, int* blockCount, AssetFactory* assetFactory, BlockColor color);
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