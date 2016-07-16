#ifndef BALL_H
#define BALL_H

#include <iostream>
#include <cmath>
#include <climits>

#include "GameEntity.h"
#include "Paddle.h"
#include "Block.h"
#include "AssetFactory.h"
#include "StateMachine.h"
#include "Sound.h"

typedef enum
{
	LOST_ST,
	WAITING_ST,
	FLYING_ST
} BallState;

class Ball : public GameEntity, public IKeyboardEventHandler
{
private:
	Paddle* paddle;
	StateMachine<BallState>* state;
	Sound *paddleSound, *blockSound;
	AssetFactory* assetFactory;
	
public:
	Ball(Paddle*, AssetFactory* assetFactory);
	~Ball();

	void handleKeyboardEvents(const Uint8*);
	void update(int frameTime);

	char* type();

	void resolveCollision(GameEntity* collider, GameEntity* object);

private:
	void updateVelocityWithAngle(float degrees);
	void stateChanged(BallState prevState, BallState currState);
};

#endif