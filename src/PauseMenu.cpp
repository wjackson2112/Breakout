#include "PauseMenu.h"

PauseMenu::PauseMenu(AssetFactory* assetFactory)
: Menu(this->x, this->y, this->num_rows, this->row_height, this->row_padding, this->num_cols, this->col_width, this->col_padding, assetFactory)
{
	this->add_menu_item(new Button("./png/ResumeGame.png", assetFactory,  RESUME_GAME), 0, 0);
	this->add_menu_item(new Button("./png/NewGame.png", assetFactory, NEW_GAME), 1, 0);
	this->add_menu_item(new Button("./png/Options.png", assetFactory, OPTIONS), 2, 0);
	this->add_menu_item(new Button("./png/QuitGame.png", assetFactory, QUIT_GAME), 3, 0);
	this->add_menu_item(new Button("./png/QuitToDesktop.png", assetFactory, QUIT_PROGRAM), 4, 0);	
}