#ifndef VIDEO_OPTIONS_MENU_H
#define VIDEO_OPTIONS_MENU_H

#include "Menu.h"
#include "AssetFactory.h"
#include "Options.h"

class VideoOptionsMenu : public Menu
{
public:
	VideoOptionsMenu(AssetFactory* assetFactory, Options* options);
};

#endif