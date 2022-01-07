#include "stdafx.h"
#include "Eat.h"

Eat::Eat(const int& x, const int& y)
{
	character = 'O';
	this->x = x;
	this->y = y;
}

int& Eat::getX()
{
	return x;
}

int& Eat::getY()
{
	return y;
}

char Eat::getCharacter()
{
	return character;
}