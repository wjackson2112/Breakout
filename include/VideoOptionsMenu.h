#ifndef VIDEO_OPTIONS_MENU_H
#define VIDEO_OPTIONS_MENU_H

#include "Menu.h"

class VideoOptionsMenu : public Menu
{
	int num_rows = 0;
	int num_cols = 0;
	int x = 100;
	int y = 100;
	int row_height= 75;
	int row_padding = 25;
	int col_width = 100;
	int col_padding = 25;
	
public:

	VideoOptionsMenu(AssetFactory* assetFactory);
};

#endif