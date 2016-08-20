#include "MenuEntity.h"

MenuEntity::MenuEntity(string texture_file, AssetFactory* assetFactory, Options* options)
	: Entity::Entity(texture_file, assetFactory)
{
	this->options = options;
}

void MenuEntity::setRect(Rect rect)
{
	Entity::setRect(rect);
}