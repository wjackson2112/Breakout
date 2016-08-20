#include "Options.h"

void Options::save()
{
	//TODO: Actually save out some options
	std::cout << "Saving Options" << std::endl;
}

void Options::load()
{
	//TOOD: Actually load up some options
	std::cout << "Loading Options" << std::endl;
	this->audio.masterVolume.value = 100;
}