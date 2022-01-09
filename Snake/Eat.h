#pragma once
#include "Objects.h"
#include "Engine.h"
#include "Direction.h"

class Eat : virtual public Objects
{
	char character;
	int x;
	int y;

public:

	Eat(const int& x, const int& y);
	int& getX() override;
	int& getY() override;
	char getCharacter() override;
	Direction getDirection() override { return Direction::statical; };
	virtual void setDirection(const Direction& direction) override {};
};