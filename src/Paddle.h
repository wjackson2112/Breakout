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

	void handleEvents(const Uint8*);
	void update(int frameTime);
	void render(SDL_Renderer*);
	void resolveCollision(PhysicsEntity*);

	Paddle* clone() const;
	Paddle* collisionClone() const;

	SDL_Point getCenter();
	SDL_Point getOrigin();
	SDL_Point getVelocity();
	SDL_Point getSize();

	bool isDeletable();
};

#endif