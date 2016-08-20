#ifndef OPTIONS_H
#define OPTIONS_H

#include <iostream>

typedef struct SliderOption_t
{
	int min;
	int max;
	int value;
} SliderOption;

typedef struct Audio_t
{
	SliderOption masterVolume;
	SliderOption musicVolume;
	SliderOption sfxVolume;
} Audio;

class Options
{
public:
	Audio audio;

	void save();
	void load();
};

#endif