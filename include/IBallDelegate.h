#ifndef IBALL_DELEGATE_H
#define IBALL_DELEGATE_H

#include "Ball.h"

class IBallDelegate
{
public:
	virtual void ballLost() = 0;
};

#endif