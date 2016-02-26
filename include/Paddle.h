#ifndef PADDLE_H
#define PADDLE_H

#include <iostream>
#include "PhysicsEntity.h"

class Paddle : public PhysicsEntity
{
private:
	float accelX, accelY;

public:
	int width = Globals::paddleWidth;
	int height = Globals::paddleHeight;

	float max_vel = width * 2.5;
	int accel = max_vel * 5;

	Paddle(float x, float y);
	~Paddle();

	void handleMouseEvents(int mouseState, int x, int y);
	void handleKeyboardEvents(const Uint8*);
	void handleGameEvents(const Uint8* events);
	void update(int frameTime);
	void render(SDL_Renderer*);

	char* type();

	void resolveCollision(PhysicsEntity* collider, PhysicsEntity* object);

	SDL_Point getCenter();
	SDL_Point getOrigin();
	SDL_Point getVelocity();
	SDL_Point getSize();

	bool isDeletable();
};

#endif