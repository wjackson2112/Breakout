#include "Sound.h"

Sound::Sound(string filename, Options* options)
{
	ALenum format;
	ALsizei size;
	ALsizei freq;
	ALboolean loop;
	ALvoid* data;
	ALuint error;

	this->options = options;

	alGenBuffers(1, &(this->buffer));
	if(!checkError(__func__)) return;

	alutLoadWAVFile((ALbyte*) filename.c_str(), &format, &data, &size, &freq, &loop);
	if(!checkError(__func__)) return;


	alBufferData(this->buffer, format, data, size, freq);
	if(!checkError(__func__)) return;

	alutUnloadWAV(format,data,size,freq);
	if(!checkError(__func__)) return;


	alGenSources(1, &(this->source));
	if(!checkError(__func__)) return;

	alSourcei(source, AL_BUFFER, buffer);
	if(!checkError(__func__)) return;
}

Sound::~Sound()
{
	alDeleteSources(1, &source);
	alDeleteBuffers(1, &buffer);
}

void Sound::play()
{
	//Apply Master Volume Setting
	alSourcef(source, AL_GAIN, ((float) stof(options->getValue("sound.volume")))/100);

	alSourcePlay(source);
}

void Sound::stop()
{
	alSourceStop(source);
}

void Sound::rewind()
{
	alSourceRewind(source);
}

void Sound::pause()
{
	alSourcePause(source);
}

bool Sound::checkError(string source)
{
	ALenum error;

	if((error = alGetError()) != AL_NO_ERROR)
	{
		std::cout << source << " gave error ";
		switch(error)
		{
			case AL_NO_ERROR:
				std::cout << "AL_NO_ERROR" << std::endl;
			case AL_INVALID_NAME:
				std::cout << "AL_INVALID_NAME" << std::endl;
				break;
			case AL_INVALID_ENUM:
				std::cout << "AL_INVALID_ENUM" << std::endl;
				break;
			case AL_INVALID_VALUE:
				std::cout << "AL_INVALID_VALUE" << std::endl;
				break;
			case AL_INVALID_OPERATION:
				std::cout << "AL_INVALID_OPERATION" << std::endl;
				break;
			case AL_OUT_OF_MEMORY:
				std::cout << "AL_OUT_OF_MEMORY" << std::endl;
				break;
			default:
				std::cout << "UNKNOWN AL ERROR" << std::endl;
				break;
		}
		return false;
	}
	return true;
}