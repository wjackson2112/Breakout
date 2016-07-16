#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <cstdlib>
#include "GameEntity.h"
#include "Ball.h"
#include "AssetFactory.h"
#include "StateMachine.h"
#include "Effects.h"

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

class Block : public GameEntity
{
private:
	StateMachine<BlockState>* state;
	AssetFactory* assetFactory;
	Effects* effects;

public:
	Block(int x, int y, int width, int height, int* blockCount, AssetFactory* assetFactory, BlockColor color);
	~Block();

	void render(SDL_Renderer*);

	char* type();

	void resolveCollision(GameEntity* collider, GameEntity* object);

	bool isDeletable();

	void alphaTransitionComplete();

private:
	void stateChanged(BlockState prevState, BlockState currState);

};

#endif