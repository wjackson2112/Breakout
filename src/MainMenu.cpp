#include "MainMenu.h"

#define X_OFFSET 100
#define Y_OFFSET 100
#define NUM_ROWS 3
#define ROW_HEIGHT 75
#define ROW_PADDING 25
#define NUM_COLS 1
#define COL_WIDTH 100
#define COL_PADDING 25

MainMenu::MainMenu(AssetFactory* assetFactory)
	: Menu(X_OFFSET, Y_OFFSET, NUM_ROWS, ROW_HEIGHT, ROW_PADDING, NUM_COLS, COL_WIDTH, COL_PADDING, assetFactory)
{
	this->add_menu_item(new Button("./png/NewGame.png", assetFactory, NEW_GAME), 0, 0);
	this->add_menu_item(new Button("./png/Options.png", assetFactory, OPTIONS), 1, 0);
	this->add_menu_item(new Button("./png/QuitToDesktop.png", assetFactory, QUIT_PROGRAM), 2, 0);
}