#ifndef PHYSICS_ENTITY_H
#define PHYSICS_ENTITY_H

#include <SDL2/SDL.h>
#include "Entity.h"
#include "IGameEventHandler.h"
#include "IKeyboardEventHandler.h"

class GameEntity : public Entity
{
protected:
	float velX, velY;
public:
	float max_vel;

	GameEntity(string texture_file, AssetFactory* assetFactory);
	virtual ~GameEntity(){};

	virtual void resolveCollision(GameEntity* collider, GameEntity* object){};
	virtual SDL_Point getVelocity();

	virtual bool isDeletable();
};

#endif