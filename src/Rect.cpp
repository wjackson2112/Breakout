#include "Rect.h"

Rect::Rect()
{
	this->x = 0.0;
	this->y = 0.0;
	this->w = 0.0;
	this->h = 0.0;
}

Rect::Rect(double x, double y, double w, double h)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

bool Rect::contains(double x, double y)
{
	if(x > this->x &&
	   x < this->x + this->w &&
	   y > this->y &&
	   y < this->y + this->h)
	{
		return true;
	}

	return false;
}

void Rect::setOrigin(double x, double y)
{
	this->x = x;
	this->y = y;
}

Point Rect::getOrigin()
{
	return Point(this->x, this->y);
}

void Rect::setCenter(double x, double y)
{
	this->x = x - this->w/2;
	this->y = y - this->h/2;
}

Point Rect::getCenter()
{
	return Point(this->x + this->w/2, this->y + this->h/2);
}

void Rect::setSize(double w, double h)
{
	this->w = w;
	this->h = h;
}