#ifndef PADDLE_H
#define PADDLE_H

#include <iostream>
#include "PhysicsEntity.h"

class Paddle : public PhysicsEntity
{
private:
	float accelX, accelY;
	int accel = 1000;
public:
	int width = 60.0;
	int height = 20.0;

	Paddle(float x, float y);
	~Paddle();

	void handleKeyboardEvents(const Uint8*);
	void handleGameEvents(const Uint8* events);
	void update(int frameTime);
	void render(SDL_Renderer*);
	void resolveCollision(PhysicsEntity* collider, PhysicsEntity* object);

	SDL_Point getCenter();
	SDL_Point getOrigin();
	SDL_Point getVelocity();
	SDL_Point getSize();

	bool isDeletable();
};

#endif