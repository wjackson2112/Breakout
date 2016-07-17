#include "VideoOptionsMenu.h"

#define X_OFFSET 150
#define Y_OFFSET 100
#define NUM_ROWS 0
#define ROW_HEIGHT 30
#define ROW_PADDING 15
#define NUM_COLS 1
#define COL_WIDTH 250
#define COL_PADDING 25

VideoOptionsMenu::VideoOptionsMenu(AssetFactory* assetFactory)
	: Menu(X_OFFSET, Y_OFFSET, NUM_ROWS, ROW_HEIGHT, ROW_PADDING, NUM_COLS, COL_WIDTH, COL_PADDING, assetFactory)
{

}