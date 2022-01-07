#pragma once
#include "Objects.h"
#include "Engine.h"
#include "Direction.h"

class SnakeHead : virtual public Objects
{
	char character;
	int x;
	int y;
	Direction direction;

public:

	SnakeHead(const int& x, const int& y);
	int& getX() override;
	int& getY() override;
	char getCharacter() override;
	Direction getDirection() override;
	void setDirection(const Direction& direction) override;
};
