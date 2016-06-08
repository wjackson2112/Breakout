#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "Menu.h"

class MainMenu : public Menu
{
	int num_rows = 3;
	int num_cols = 1;

public:

	MainMenu(int x, int y, int row_height, int row_padding, int col_width, int col_padding, AssetFactory* assetFactory);
};

#endif