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
#include "Collider.h"
#include "Globals.h"

class GameManager : public IEventHandler
{
private:
	std::vector<PhysicsEntity*> physicsEntities;
	std::vector<UIEntity*> uiEntities;
	int blockCount;
	bool quit;
	void detectCollisions();
	void resetLevel();

	void gameWon();
	void gameLost();

public:
	GameManager();
	~GameManager();

	void blockDisappearing();
	void ballLost();
	void ballsDepleted();

	bool shouldQuit();
	void render(SDL_Renderer*);
	void update(int frameTime);

	char* type();

	void handleKeyboardEvents(const Uint8*);
	void handleGameEvents(const Uint8* events);
};

#endif