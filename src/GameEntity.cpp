#include "GameEntity.h"

GameEntity::GameEntity(string texture_file, AssetFactory* assetFactory)
	: Entity::Entity(texture_file, assetFactory)
{
	velX = 0;
	velY = 0;
	max_vel = 0;
}

SDL_Point GameEntity::getVelocity()
{
	SDL_Point velocity = {this->velX, this->velY};
	return velocity;
}

bool GameEntity::isDeletable()
{
	return false;
}