#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <vector>
#include <cstdlib>

#include "IEventHandler.h"
#include "EventManager.h"
#include "Entity.h"
#include "Paddle.h"
#include "Ball.h"
#include "Block.h"
#include "Globals.h"

class GameManager
{
private:
	std::vector<Entity*> entities;
	int blockCount;
	bool quit;
	void handleEvents();
	void detectCollisions();
	void resetLevel();
public:
	GameManager();
	~GameManager();
	bool shouldQuit();
	void render(SDL_Renderer*);
	void update(int frameTime);
};

#endif