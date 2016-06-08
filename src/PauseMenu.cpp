#include "PauseMenu.h"

PauseMenu::PauseMenu(int x, int y, int row_height, int row_padding, int col_width, int col_padding, AssetFactory* assetFactory)
: Menu(x, y, this->num_rows, row_height, row_padding, this->num_cols, col_width, col_padding, assetFactory)
{
	this->add_menu_item(new Button("./png/ResumeGame.png", assetFactory,  RESUME_GAME), 0, 0);
	this->add_menu_item(new Button("./png/NewGame.png", assetFactory, NEW_GAME), 1, 0);
	this->add_menu_item(new Button("./png/Options.png", assetFactory, OPTIONS), 2, 0);
	this->add_menu_item(new Button("./png/QuitGame.png", assetFactory, QUIT_GAME), 3, 0);	
}