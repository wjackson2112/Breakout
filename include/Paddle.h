#ifndef PADDLE_H
#define PADDLE_H

#include <iostream>
#include "GameEntity.h"
#include "AssetFactory.h"
#include "StateMachine.h"

class Paddle : public GameEntity, public IKeyboardEventHandler
{
private:
	float accelX, accelY;
	AssetFactory* assetFactory;
	
public:

	float max_vel;
	int accel;

	Paddle(float x, float y, AssetFactory* assetFactory);
	~Paddle();

	void handleKeyboardEvents(const Uint8*);
	void update(int frameTime);

	char* type();
};

#endif