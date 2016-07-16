#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <vector>
#include <cstdlib>
#include <cstring>

#include "IGameEventHandler.h"
#include "EventManager.h"
#include "GameEntity.h"
#include "UIEntity.h"
#include "Paddle.h"
#include "Ball.h"
#include "Block.h"
#include "BallsIndicator.h"
#include "Collider.h"
#include "Globals.h"

class GameManager : public IGameEventHandler
{
private:
	std::vector<GameEntity*> physicsEntities;
	std::vector<UIEntity*> uiEntities;
	AssetFactory* assetFactory;
	SDL_Texture* gameTexture;
	int blockCount;
	bool pause, visible;
	void detectCollisions();
	void resetLevel();
	void clearLevel();

	void gameWon();
	void gameLost();

public:
	GameManager(AssetFactory* assetFactory, SDL_Renderer* gRenderer);
	~GameManager();

	void render(SDL_Renderer*);
	void update(int frameTime);

	char* type();
	
	void handleGameEvents(const Uint8* events);
};

#endif