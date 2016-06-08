#ifndef PAUSE_MENU_H
#define PAUSE_MENU_H

#include "Menu.h"

class PauseMenu : public Menu
{
	int num_rows = 5;
	int num_cols = 1;

public:

	PauseMenu(int x, int y, int row_height, int row_padding, int col_width, int col_padding, AssetFactory* assetFactory);
};

#endif