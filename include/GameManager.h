#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <vector>
#include <cstdlib>
#include <cstring>

#include "IEventHandler.h"
#include "EventManager.h"
#include "PhysicsEntity.h"
#include "UIEntity.h"
#include "Paddle.h"
#include "Ball.h"
#include "Block.h"
#include "BallsIndicator.h"
#include "Globals.h"

class GameManager : public IBlockDelegate, IBallDelegate
{
private:
	std::vector<PhysicsEntity*> physicsEntities;
	std::vector<UIEntity*> uiEntities;
	int blockCount;
	bool quit;
	void handleKeyboardEvents();
	void handleGameEvents();
	void detectCollisions();
	void resetLevel();
public:
	GameManager();
	~GameManager();

	void blockDisappearing();
	void ballLost();

	bool shouldQuit();
	void render(SDL_Renderer*);
	void update(int frameTime);
};

#endif