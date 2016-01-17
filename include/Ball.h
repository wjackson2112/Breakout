#ifndef BALL_H
#define BALL_H

#include <iostream>
#include <cmath>
#include <climits>

#include "PhysicsEntity.h"
#include "Paddle.h"
#include "Block.h"

enum states
{
	WAITING_ST,
	FLYING_ST
};

class Ball : public PhysicsEntity
{
private:
	Paddle* paddle;
	int machineState;
	void updateVelocityWithAngle(float degrees);
public:
	int width = 20.0;
	int height = 20.0;

	float max_vel = 300;

	Ball(Paddle*);
	~Ball();

	void handleEvents(const Uint8*);
	void update(int frameTime);
	void render(SDL_Renderer*);
	void resolveCollision(PhysicsEntity*);

	Ball* clone() const;
	Ball* collisionClone() const;

	SDL_Point getCenter();
	SDL_Point getOrigin();
	SDL_Point getVelocity();
	SDL_Point getSize();

	bool isDeletable();
};

#endif