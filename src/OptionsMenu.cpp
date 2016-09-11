#include "OptionsMenu.h"

#define X_OFFSET 150
#define Y_OFFSET 100
#define NUM_ROWS 2
#define ROW_HEIGHT 30
#define ROW_PADDING 15
#define NUM_COLS 1
#define COL_WIDTH 250
#define COL_PADDING 25

OptionsMenu::OptionsMenu(AssetFactory* assetFactory, Options* options)
	: Menu(X_OFFSET, Y_OFFSET, NUM_ROWS, ROW_HEIGHT, ROW_PADDING, NUM_COLS, COL_WIDTH, COL_PADDING)
{
	this->add_menu_item(new Label("./png/Volume.png", assetFactory, options), 0, 0);
	this->add_menu_item(new Slider(assetFactory, options, "sound.volume", 0, 100, 0), 0, 1);
}