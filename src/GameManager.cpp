#include "GameManager.h"

GameManager::GameManager(AssetFactory* assetFactory)
{
	srand(time(NULL));
	pause = true;
	visible = false;
	EventManager::Instance()->registerHandler(this);
	this->assetFactory = assetFactory;
	this->resetLevel();
}

GameManager::~GameManager()
{
	for(std::vector<UIEntity*>::iterator it=uiEntities.begin(); it!=uiEntities.end();)
	{
		delete * it;
		it = uiEntities.erase(it);
	}

	for(std::vector<PhysicsEntity*>::iterator it=physicsEntities.begin(); it!=physicsEntities.end();)
	{
		delete * it;
		it = physicsEntities.erase(it);
	}

	EventManager::Instance()->deregisterHandler(this);
}

void GameManager::gameWon()
{
	EventManager::Instance()->reportGameEvent(QUIT_GAME);
}

void GameManager::gameLost()
{
	EventManager::Instance()->reportGameEvent(QUIT_GAME);
}

void GameManager::resetLevel()
{
	if(uiEntities.size() >= 0){
		for(std::vector<UIEntity*>::iterator it=uiEntities.begin(); it!=uiEntities.end();)
		{
			delete * it;
			it = uiEntities.erase(it);
		}
		uiEntities.clear();
	}

	uiEntities.push_back(new BallsIndicator(0, Globals::screenHeight - Globals::ballHeight, assetFactory));

	if(physicsEntities.size() >= 0){
		for(std::vector<PhysicsEntity*>::iterator it=physicsEntities.begin(); it!=physicsEntities.end();)
		{
			delete * it;
			it = physicsEntities.erase(it);
		}
		physicsEntities.clear();
	}

	blockCount = 0;
	physicsEntities.push_back(new Paddle((Globals::fieldWidth / 2) - (Globals::paddleWidth / 2), Globals::screenHeight - Globals::paddleHeight, assetFactory));
	physicsEntities.push_back(new Ball((Paddle*) physicsEntities[0], assetFactory));

	for(int x = 0; x + Globals::blockWidth <= Globals::fieldWidth; x+=Globals::blockWidth)
	{
		for(int y = 0; y < Globals::blockHeight * 6; y += Globals::blockHeight)
		{
			physicsEntities.push_back(new Block(Globals::xOffset + x, Globals::yOffset + y, Globals::blockWidth, Globals::blockHeight, &blockCount, this->assetFactory, (BlockColor) (y/Globals::blockHeight)));		
			blockCount++;
		}
	}

	EventManager::Instance()->reportGameEvent(BALL_ADDED);
	EventManager::Instance()->reportGameEvent(BALL_ADDED);
	EventManager::Instance()->reportGameEvent(BALL_ADDED);
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

				Collider* entityACopy = new Collider(entityA);
				Collider* entityBCopy = new Collider(entityB);
				entityA->resolveCollision(entityBCopy, entityB);
				entityB->resolveCollision(entityACopy, entityA);
				delete(entityACopy);
				delete(entityBCopy);
			}
		}
	}
}

void GameManager::render(SDL_Renderer* gRenderer)
{
	//if(!visible)
	//{
	//	return;
	//}

	SDL_Rect backgroundRect = {Globals::xOffset, Globals::yOffset, Globals::fieldWidth, Globals::fieldHeight};
	SDL_SetRenderDrawColor(gRenderer, 0x10, 0x10, 0x10, 0xFF);
	SDL_RenderFillRect(gRenderer, &backgroundRect);

	for(auto &entity : physicsEntities)
	{
		entity->render(gRenderer);
	}

	for(auto &entity : uiEntities)
	{
		entity->render(gRenderer);
	}
}

void GameManager::update(int frameTime)
{
	static bool levelComplete = false;

	if(pause)
	{
		return;
	}

	for(auto &entity : uiEntities)
	{
		entity->update(frameTime);
	}

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
		gameWon();
	}
	
	detectCollisions();
}

char* GameManager::type()
{
	return "GameManager";
}

void GameManager::handleMouseEvents(int mouseState, int x, int y)
{
	
}

void GameManager::handleKeyboardEvents(const Uint8* keyStates)
{

}

void GameManager::handleGameEvents(const Uint8* events)
{
	if(events[BLOCK_DISAPPEARED])
	{
		blockCount -= events[BLOCK_DISAPPEARED];
	}

	if(events[BALLS_DEPLETED])
	{
		gameLost();
	}

	if(events[NEW_GAME])
	{
		visible = true;
		pause = false;
		this->resetLevel();
	}

	if(events[PAUSE_GAME])
	{
		pause = true;
	}

	if(events[RESUME_GAME])
	{
		pause = false;
	}

	if(events[QUIT_GAME])
	{
		visible = false;
		this->resetLevel();
	}
}