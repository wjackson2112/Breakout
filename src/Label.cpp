#include "Label.h"

Label::Label(string texture_file, AssetFactory* assetFactory, Options* options)
	: MenuEntity::MenuEntity(texture_file, assetFactory, options)
{

}

char* Label::type()
{
	return "Label";
}
