#ifndef OPTIONS_MENU_H
#define OPTIONS_MENU_H

#include "Menu.h"
#include "AssetFactory.h"
#include "Options.h"

class OptionsMenu : public Menu
{
public:
	OptionsMenu(AssetFactory* assetFactory, Options* options);
};

#endif