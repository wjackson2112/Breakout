#include "OptionsMenu.h"

OptionsMenu::OptionsMenu(AssetFactory* assetFactory)
: Menu(this->x, this->y, this->num_rows, this->row_height, this->row_padding, this->num_cols, this->col_width, this->col_padding, assetFactory)
{
	this->add_menu_item(new Button("./png/VideoOptions.png", assetFactory, VIDEO_OPTIONS), 0, 0);
	this->add_menu_item(new Button("./png/AudioOptions.png", assetFactory, AUDIO_OPTIONS), 1, 0);
}