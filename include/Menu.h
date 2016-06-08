#ifndef MENU_H
#define MENU_H

#include <vector>
#include "Button.h"
#include "AssetFactory.h"

class Menu
{
private:
	int num_rows, row_height, row_padding;
	int num_cols, col_width, col_padding;
	SDL_Rect rect;
	std::vector<MenuEntity*> menuItems;
public:
	Menu(int x, int y, int num_rows, int row_height, int row_padding, int num_cols, int col_width, int col_padding, AssetFactory* assetFactory);
	void add_menu_item(MenuEntity* item, int row, int col);
	void render(SDL_Renderer *gRenderer);
};

#endif