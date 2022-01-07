#pragma once
#include "stdafx.h"
#include "Direction.h"

class Objects
{
public:
	Objects() {}
	virtual ~Objects() {}
	virtual int& getX() = 0;
	virtual int& getY() = 0;
	virtual char getCharacter() = 0;
	virtual Direction getDirection() = 0;
	virtual void setDirection(const Direction& direction) = 0;
};