#include "MainMenu.h"

MainMenu::MainMenu(AssetFactory* assetFactory)
: Menu(this->x, this->y, this->num_rows, this->row_height, this->row_padding, this->num_cols, this->col_width, this->col_padding, assetFactory)
{
	this->add_menu_item(new Button("./png/NewGame.png", assetFactory, NEW_GAME), 0, 0);
	this->add_menu_item(new Button("./png/Options.png", assetFactory, OPTIONS), 1, 0);
	this->add_menu_item(new Button("./png/QuitToDesktop.png", assetFactory, QUIT_PROGRAM), 2, 0);
}