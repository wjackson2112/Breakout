#include "Menu.h"

//TODO: Find a way to eliminate the "num_rows" and "num_cols" vars here
//They should just be dynamically updated based on adding items to the menu
Menu::Menu(int x, int y, int num_rows, int row_height, int row_padding, int num_cols, int col_width, int col_padding)
{
	this->rect.x = x;
	this->rect.y = y;
	this->rect.w = (num_cols * col_width) + ((num_cols - 1) * col_padding);
	this->rect.h = (num_rows * row_height) + ((num_rows - 1) * row_padding);
	this->num_rows = num_rows;
	this->row_height = row_height;
	this->row_padding = row_padding;
	this->num_cols = num_cols;
	this->col_width = col_width;
	this->col_padding = col_padding;

	this->menuItems.resize(num_rows * num_cols);
}

void Menu::add_menu_item(MenuEntity* item, int row, int col)
{
	//Scale the texture to match the size of the menu items
	SDL_Rect orig_rect = item->getRect();
	SDL_Rect *new_rect = new SDL_Rect();

	new_rect->x = this->rect.x + (col) * (this->col_width + this->col_padding);
	new_rect->y = this->rect.y + (row) * (this->row_height + this->row_padding);
	new_rect->w = ((float) this->row_height/(float) orig_rect.h)*orig_rect.w;
	new_rect->h = this->row_height;

	item->setRect(*new_rect);

	this->menuItems[row + col] = item;
}

void Menu::render(SDL_Renderer* gRenderer)
{
	for(auto &item : menuItems)
	{
		item->render(gRenderer);
	}
}
