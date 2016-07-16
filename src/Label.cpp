#include "Label.h"

Label::Label(string texture_file, AssetFactory* assetFactory)
	: MenuEntity::MenuEntity(texture_file, assetFactory)
{

}

char* Label::type()
{
	return "Label";
}
