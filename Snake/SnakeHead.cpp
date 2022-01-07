#include "stdafx.h"
#include "SnakeHead.h"

SnakeHead::SnakeHead(const int& x, const int& y)
{
	character = '#';
	this->x = x;
	this->y = y;
	direction = Direction::up;
}

int& SnakeHead::getX()
{
	return x;
}

int& SnakeHead::getY()
{
	return y;
}

char SnakeHead::getCharacter()
{
	return character;
}

Direction SnakeHead::getDirection()
{
	return direction;
}

void SnakeHead::setDirection(const Direction& direction)
{
	this->direction = direction;
}