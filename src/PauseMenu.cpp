#include "PauseMenu.h"

#define X_OFFSET 150
#define Y_OFFSET 100
#define NUM_ROWS 5
#define ROW_HEIGHT 30
#define ROW_PADDING 15
#define NUM_COLS 1
#define COL_WIDTH 250
#define COL_PADDING 25

PauseMenu::PauseMenu(AssetFactory* assetFactory, Options* options)
	: Menu(X_OFFSET, Y_OFFSET, NUM_ROWS, ROW_HEIGHT, ROW_PADDING, NUM_COLS, COL_WIDTH, COL_PADDING)
{
	this->add_menu_item(new Button("./png/ResumeGame.png", assetFactory, options, RESUME_GAME), 0, 0);
	this->add_menu_item(new Button("./png/NewGame.png", assetFactory, options, NEW_GAME), 1, 0);
	this->add_menu_item(new Button("./png/Options.png", assetFactory, options, OPTIONS), 2, 0);
	this->add_menu_item(new Button("./png/QuitGame.png", assetFactory, options, QUIT_GAME), 3, 0);
	this->add_menu_item(new Button("./png/QuitToDesktop.png", assetFactory, options, QUIT_PROGRAM), 4, 0);	
}