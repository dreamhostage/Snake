#pragma once
#include <vector>
#include <chrono>
#include <thread>
#include <iostream>
#include <memory>
#include <mutex>
#include <Windows.h>
#include <random>
#include <conio.h>
#include "Objects.h"
#include "SnakeHead.h"
#include "Eat.h"

class Engine
{
	std::vector<std::string> map;
	std::vector<std::unique_ptr<Objects>> objects;
	std::string tmpStr;
	std::mutex dataMutex;
	bool gameOver;
	int frameRate = 50;
	int score = 0;
	int tempX;
	int tempY;

	void parseObjects();
	void draw();
	void moveSnake();
	void keyProcessor();
	void checkGameOver(std::thread& keysThread);
	void checkMoving();
	void generateEat();
	void createObjects();
	void gameMenu();
	
public:

	const static int x = 20;
	const static int y = 70;
	Engine();
	void run();
};