#ifndef AUDIO_OPTIONS_MENU_H
#define AUDIO_OPTIONS_MENU_H

#include "Menu.h"
#include "Options.h"

class AudioOptionsMenu : public Menu
{	
public:
	AudioOptionsMenu(AssetFactory* assetFactory, Options* options);
};

#endif