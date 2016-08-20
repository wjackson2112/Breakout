#ifndef SOUND_H
#define SOUND_H

#include <AL/alut.h>
#include <string>
#include <iostream>
#include "Options.h"

using namespace std;

class Sound
{
private:
	ALuint buffer;
	ALuint source;
	Options* options;

	bool checkError(string source);
public:
	Sound(string filename, Options* options);
	~Sound();
	void play();
	void stop();
	void rewind();
	void pause();
};

#endif