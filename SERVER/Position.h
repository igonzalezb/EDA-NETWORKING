#pragma once
#ifndef _POSITION_H
#define _POSITION_H


class Position
{
public:
	Position();
	double getX();
	double getY();
	void setX(double _x);
	void setY(double _y);

private:
	double x;
	double y;

};



#endif // !_POSITION_H




