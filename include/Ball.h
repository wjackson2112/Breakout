#ifndef BALL_H
#define BALL_H

#include <iostream>
#include <cmath>
#include <climits>

#include "PhysicsEntity.h"
#include "Paddle.h"
#include "Block.h"
#include "TextureFactory.h"
#include "StateMachine.h"

typedef enum
{
	LOST_ST,
	WAITING_ST,
	FLYING_ST
} BallState;

class Ball : public PhysicsEntity
{
private:
	Paddle* paddle;
	StateMachine<BallState>* state;
	void updateVelocityWithAngle(float degrees);
	SDL_Texture* texture;
	TextureFactory* textureFactory;

	void stateChanged(BallState prevState, BallState currState);
public:
	int width = Globals::ballWidth;
	int height = Globals::ballHeight;

	float max_vel = width * 15;

	Ball(Paddle*, TextureFactory* textureFactory);
	~Ball();

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