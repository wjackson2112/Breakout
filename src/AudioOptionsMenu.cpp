#include "AudioOptionsMenu.h"

#define X_OFFSET 150
#define Y_OFFSET 100
#define NUM_ROWS 3
#define ROW_HEIGHT 30
#define ROW_PADDING 15
#define NUM_COLS 1
#define COL_WIDTH 250
#define COL_PADDING 25

AudioOptionsMenu::AudioOptionsMenu(AssetFactory* assetFactory)
	: Menu(X_OFFSET, Y_OFFSET, NUM_ROWS, ROW_HEIGHT, ROW_PADDING, NUM_COLS, COL_WIDTH, COL_PADDING, assetFactory)
{
	this->add_menu_item(new Label("./png/NewGame.png", assetFactory), 0, 0);
	this->add_menu_item(new Slider(assetFactory), 0, 1);
}