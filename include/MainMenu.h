#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "Menu.h"

class MainMenu : public Menu
{
	int num_rows = 3;
	int num_cols = 1;
	int x = 100;
	int y = 100;
	int row_height= 75;
	int row_padding = 25;
	int col_width = 100;
	int col_padding = 25;

public:

	MainMenu(AssetFactory* assetFactory);
};

#endif