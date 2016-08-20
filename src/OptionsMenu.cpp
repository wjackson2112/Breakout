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
	this->add_menu_item(new Button("./png/VideoOptions.png", assetFactory, options, VIDEO_OPTIONS), 0, 0);
	this->add_menu_item(new Button("./png/AudioOptions.png", assetFactory, options, AUDIO_OPTIONS), 1, 0);
}