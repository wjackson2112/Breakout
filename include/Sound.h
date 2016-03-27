#ifndef SOUND_H
#define SOUND_H

#include <AL/alut.h>
#include <string>
#include <iostream>

using namespace std;

class Sound
{
private:
	ALuint buffer;
	ALuint source;
public:
	Sound(string filename);
	~Sound();
	void play();
	void stop();
	void rewind();
	void pause();
};

#endif