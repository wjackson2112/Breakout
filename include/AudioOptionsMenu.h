#ifndef AUDIO_OPTIONS_MENU_H
#define AUDIO_OPTIONS_MENU_H

#include "Menu.h"

class AudioOptionsMenu : public Menu
{
	int num_rows = 2;
	int num_cols = 1;
	
public:

	AudioOptionsMenu(int x, int y, int row_height, int row_padding, int col_width, int col_padding, AssetFactory* assetFactory);
};

#endif