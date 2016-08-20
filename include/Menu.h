#ifndef MENU_H
#define MENU_H

#include <vector>
#include "Button.h"
#include "Label.h"
#include "Slider.h"
#include "EventManager.h"
#include "Options.h"

class Menu
{
protected:
	int num_rows, row_height, row_padding;
	int num_cols, col_width, col_padding;
	SDL_Rect rect;
	std::vector<MenuEntity*> menuItems;
public:
	Menu(int x, int y, int num_rows, int row_height, int row_padding, int num_cols, int col_width, int col_padding);
	void add_menu_item(MenuEntity* item, int row, int col);
	void add_floating_menu_item(MenuEntity* item, int x, int y);
	void handleMousePress(int mouseButton, int x, int y);
	void handleMouseDrag(int mouseButton, int prevX, int prevY, int currX, int currY);
	void handleMouseRelease(int mouseButton, int x, int y);
	void render(SDL_Renderer *gRenderer);
	void update(int frameTime);
};

#endif