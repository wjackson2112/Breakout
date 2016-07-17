#ifndef RECT_H
#define RECT_H

class Point
{
public:
	double x, y;
	Point(double x, double y){this->x = x; this->y = y;}
};

class Rect
{
public:
	double x, y, w, h;

	Rect();
	Rect(double x, double y, double w, double h);

	bool contains(double x, double y);
	
	void  setOrigin(double x, double y);
	Point getOrigin();

	void  setCenter(double x, double y);
	Point getCenter();
	
	void setSize(double w, double h);
};

#endif