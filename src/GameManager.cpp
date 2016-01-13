#include "GameManager.h"

GameManager::GameManager()
{
	srand(time(NULL));
	quit = false;
	resetLevel();
}

GameManager::~GameManager()
{
	for(auto &entity : physicsEntities)
	{
		delete(entity);
	}
}

void GameManager::resetLevel()
{
	if(physicsEntities.size() >= 0){
		for(std::vector<PhysicsEntity*>::iterator it=physicsEntities.begin(); it!=physicsEntities.end();)
		{
			delete * it;
			it = physicsEntities.erase(it);
		}
		physicsEntities.clear();
	}

	blockCount = 0;
	physicsEntities.push_back(new Paddle(30, SCREEN_HEIGHT - 40));
	physicsEntities.push_back(new Ball((Paddle*) physicsEntities[0]));

	for(int x = 0; x < SCREEN_WIDTH; x+=40)
	{
		for(int y = 0; y < 240; y+= 40)
		{
			physicsEntities.push_back(new Block(x, y, &blockCount, this));		
			blockCount++;	
		}
	}
}

bool GameManager::shouldQuit()
{
	return quit;
}

void GameManager::handleEvents()
{
	SDL_Event e;
	while( SDL_PollEvent( &e ) != 0 )
 	{
 		if(e.type == SDL_QUIT)
 		{
 			quit = true;
 		}
 	}
 	EventManager::Instance()->handleEvents();
}

void GameManager::detectCollisions()
{
	for(auto &entityA : physicsEntities)
	{
		for(auto &entityB : physicsEntities)
		{
			if(entityA != entityB){

				SDL_Point originA, originB;
				SDL_Point sizeA, sizeB;

				int leftA, leftB;
				int rightA, rightB;
				int topA, topB;
				int bottomA, bottomB;

				originA = entityA->getOrigin();
				originB = entityB->getOrigin();
				sizeA = entityA->getSize();
				sizeB = entityB->getSize();

				leftA = originA.x;
				rightA = originA.x + sizeA.x;
				topA = originA.y;
				bottomA = originA.y + sizeA.y;

				leftB = originB.x;
				rightB = originB.x + sizeB.x;
				topB = originB.y;
				bottomB = originB.y + sizeB.y;

				if(bottomA <= topB    ||
				   topA    >= bottomB ||
				   rightA  <= leftB   ||
				   leftA   >= rightB)
				{
					continue;
				}

				PhysicsEntity* entityACopy = (*entityA).collisionClone();
				PhysicsEntity* entityBCopy = (*entityB).collisionClone();
				entityA->resolveCollision(entityBCopy);
				entityB->resolveCollision(entityACopy);
				delete(entityACopy);
				delete(entityBCopy);
			}
		}
	}
}

void GameManager::render(SDL_Renderer* gRenderer)
{
	SDL_SetRenderDrawColor(gRenderer, 0x10, 0x10, 0x10, 0xFF);
	SDL_RenderClear(gRenderer);
	for(auto &entity : physicsEntities)
	{
		entity->render(gRenderer);
	}
	SDL_RenderPresent(gRenderer);
}

void GameManager::update(int frameTime)
{
	static bool levelComplete = false;

	handleEvents();

	//std::cout << "Updating" << std::endl;
	for(std::vector<PhysicsEntity*>::iterator it=physicsEntities.begin(); it!=physicsEntities.end();)
	{
		//Update the item
		(*it)->update(frameTime);

		//Delete it if it's deletable
		if((*it)->isDeletable())
		{
			delete * it;
			//std::cout << "Deleted" << std::endl;
			it = physicsEntities.erase(it);
			//std::cout << "Erased" << std::endl;
		}
		else
		{
			++it;
		}
	}

	if(blockCount <= 0)
	{
		resetLevel();
	}
	
	detectCollisions();
}

void GameManager::blockDisappearing(){
	blockCount--;
}