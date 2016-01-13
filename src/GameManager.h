#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <vector>
#include <cstdlib>
#include <cstring>

#include "IEventHandler.h"
#include "EventManager.h"
#include "Entity.h"
#include "Paddle.h"
#include "Ball.h"
#include "Block.h"
#include "Globals.h"

class GameManager : public IBlockDelegate
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

	void blockDisappearing();

	bool shouldQuit();
	void render(SDL_Renderer*);
	void update(int frameTime);
};

#endif