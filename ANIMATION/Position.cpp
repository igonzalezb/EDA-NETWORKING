#include "Position.h"

Position::Position()
{
	x = 0.0;
	y = 0.0;
}

double Position::getX()
{
	return x;
}

double Position::getY()
{
	return y;
}

void Position::setX(double _x)
{
	x = _x;
}

void Position::setY(double _y)
{
	y = _y;
}