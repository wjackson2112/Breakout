#ifndef AUDIO_OPTIONS_MENU_H
#define AUDIO_OPTIONS_MENU_H

#include "Menu.h"

class AudioOptionsMenu : public Menu
{
	int num_rows = 2;
	int num_cols = 1;
	int x = 100;
	int y = 100;
	int row_height= 75;
	int row_padding = 25;
	int col_width = 100;
	int col_padding = 25;
	
public:

	AudioOptionsMenu(AssetFactory* assetFactory);
};

#endif