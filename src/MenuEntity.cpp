#include "MenuEntity.h"

MenuEntity::MenuEntity(string texture_file, AssetFactory* assetFactory)
	: Entity::Entity(texture_file, assetFactory)
{
	
}

void MenuEntity::setRect(Rect rect)
{
	Entity::setRect(rect);
}