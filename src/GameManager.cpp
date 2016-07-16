#include "GameManager.h"

GameManager::GameManager(AssetFactory* assetFactory, SDL_Renderer* gRenderer)
{
	srand(time(NULL));
	pause = true;
	visible = false;
	
	EventManager::Instance()->registerGameEventHandler(this);

	this->assetFactory = assetFactory;
	this->gameTexture = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, Globals::fieldWidth, Globals::fieldHeight);
	this->resetLevel();
}

GameManager::~GameManager()
{
	for(std::vector<UIEntity*>::iterator it=uiEntities.begin(); it!=uiEntities.end();)
	{
		delete * it;
		it = uiEntities.erase(it);
	}

	for(std::vector<GameEntity*>::iterator it=physicsEntities.begin(); it!=physicsEntities.end();)
	{
		delete * it;
		it = physicsEntities.erase(it);
	}

	EventManager::Instance()->deregisterGameEventHandler(this);
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
		for(std::vector<GameEntity*>::iterator it=physicsEntities.begin(); it!=physicsEntities.end();)
		{
			delete * it;
			it = physicsEntities.erase(it);
		}
		physicsEntities.clear();
	}

	blockCount = 0;
	physicsEntities.push_back(new Paddle((Globals::fieldWidth / 2) - (Globals::paddleWidth / 2), Globals::fieldHeight - Globals::paddleHeight, assetFactory));
	physicsEntities.push_back(new Ball((Paddle*) physicsEntities[0], assetFactory));

	for(int x = 0; x + Globals::blockWidth <= Globals::fieldWidth; x+=Globals::blockWidth)
	{
		for(int y = 0; y < Globals::blockHeight * 6; y += Globals::blockHeight)
		{
			physicsEntities.push_back(new Block(x, y, Globals::blockWidth, Globals::blockHeight, &blockCount, this->assetFactory, (BlockColor) (y/Globals::blockHeight)));		
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

				floatRect rectA, rectB;

				int leftA, leftB;
				int rightA, rightB;
				int topA, topB;
				int bottomA, bottomB;

				rectA = entityA->getRect();
				rectB = entityB->getRect();

				leftA = rectA.x;
				rightA = rectA.x + rectA.w;
				topA = rectA.y;
				bottomA = rectA.y + rectA.h;

				leftB = rectB.x;
				rightB = rectB.x + rectB.w;
				topB = rectB.y;
				bottomB = rectB.y + rectB.h;

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
	SDL_Rect gameTextureSizeRect = {0, 0, Globals::fieldWidth, Globals::fieldHeight};
	SDL_Rect gameTexturePosRect = {Globals::xOffset, Globals::yOffset, Globals::fieldWidth, Globals::fieldHeight};

	SDL_SetRenderTarget(gRenderer, this->gameTexture);

	SDL_SetRenderDrawColor(gRenderer, 0x10, 0x10, 0x10, 0xFF);
	SDL_RenderFillRect(gRenderer, &gameTextureSizeRect);

	for(auto &entity : physicsEntities)
	{
		entity->render(gRenderer);
	}

	SDL_SetRenderTarget(gRenderer, NULL);
	SDL_RenderCopy(gRenderer, this->gameTexture, NULL, &gameTexturePosRect);

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
	for(std::vector<GameEntity*>::iterator it=physicsEntities.begin(); it!=physicsEntities.end();)
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