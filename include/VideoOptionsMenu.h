#ifndef VIDEO_OPTIONS_MENU_H
#define VIDEO_OPTIONS_MENU_H

#include "Menu.h"

class VideoOptionsMenu : public Menu
{
	int num_rows = 0;
	int num_cols = 0;
	
public:

	VideoOptionsMenu(int x, int y, int row_height, int row_padding, int col_width, int col_padding, AssetFactory* assetFactory);
};

#endif