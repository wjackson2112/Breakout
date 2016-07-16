#ifndef UI_ENTITY_H
#define UI_ENTITY_H

#include <SDL2/SDL.h>
#include "Entity.h"
#include "IGameEventHandler.h"

class UIEntity : public Entity
{
public:
	UIEntity(string texture_file, AssetFactory* assetFactory);
	virtual ~UIEntity(){};
};

#endif