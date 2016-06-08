#include "OptionsMenu.h"

OptionsMenu::OptionsMenu(int x, int y, int row_height, int row_padding, int col_width, int col_padding, AssetFactory* assetFactory)
: Menu(x, y, this->num_rows, row_height, row_padding, this->num_cols, col_width, col_padding, assetFactory)
{
	this->add_menu_item(new Button("./png/Options.png", assetFactory, BACK), 0, 0);
}