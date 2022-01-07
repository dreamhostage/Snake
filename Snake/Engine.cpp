#include "stdafx.h"
#include "Engine.h"

Engine::Engine()
{
	srand(time(NULL));
	tempX = 0;
	tempY = 0;
	gameOver = false;

	createObjects();
}

void Engine::createObjects()
{
	// Creating snake body
	for (int i = 0; i < 6; ++i)
	{
		objects.push_back(std::make_unique<SnakeHead>(Engine::x / 2 + i, Engine::y / 2));
	}

	// Generating eat
	generateEat();

	// Creating map
	for (int i = 0; i < x; ++i)
	{
		for (int k = 0; k < y; ++k)
		{
			if (!i)
			{
				tmpStr.push_back('#');
			}
			else if (i == x - 1)
			{
				tmpStr.push_back('#');
			}
			else if (!k)
			{
				tmpStr.push_back('#');
			}
			else if (k == y - 1)
			{
				tmpStr.push_back('#');
			}
			else
			{
				tmpStr.push_back(' ');
			}
		}
		map.push_back(tmpStr);
		tmpStr.clear();
	}
}

void Engine::parseObjects()
{
	// Move all objects to the map
	for (int i = 0; i < objects.size(); ++i)
	{
		map[objects[i].get()->getX()][objects[i].get()->getY()] = objects[i].get()->getCharacter();
	}
}

void Engine::draw()
{
	for (int i = 0; i < x; ++i)
	{
		for (int k = 0; k < y; ++k)
		{
			std::cout << map[i][k];
		}
		std::cout << '\n';
	}
	std::cout << "               >>>>>>>>>>>>>>> Score " << score << " <<<<<<<<<<<<<<<\n";
}

void Engine::run()
{
	gameMenu();
	std::thread keysThread(&Engine::keyProcessor, this);
	keysThread.detach();
	while (!gameOver)
	{
		parseObjects();
		draw();
		std::this_thread::sleep_for(std::chrono::milliseconds(frameRate));
		checkMoving();
		moveSnake();
		checkGameOver(keysThread);
		system("cls");
	}
}

void Engine::keyProcessor()
{
	// Detecting which button pressed
	char button;
	while (true)
	{
		button = _getch();

		if (button == 119)
		{
			if (objects[0].get()->getDirection() != Direction::down)
			{
				objects[0].get()->setDirection(Direction::up);
			}
		}
		else if (button == 115)
		{
			if (objects[0].get()->getDirection() != Direction::up)
			{
				objects[0].get()->setDirection(Direction::down);
			}
		}
		else if (button == 97)
		{
			if (objects[0].get()->getDirection() != Direction::right)
			{
				objects[0].get()->setDirection(Direction::left);
			}
		}
		else if (button == 100)
		{
			if (objects[0].get()->getDirection() != Direction::left)
			{
				objects[0].get()->setDirection(Direction::right);
			}
		}
		else if (button == 113)
		{
			gameOver = true;
			system("cls");
		}
		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
		std::this_thread::sleep_for(std::chrono::milliseconds(frameRate * 2));
	}
}

void Engine::moveSnake()
{
	// Snake moving engine
	for (int i = 0; i < objects.size(); ++i)
	{
		if (objects[i].get()->getCharacter() == '#')
		{
			// Borders checking
			if (objects[i].get()->getX() > 1 && objects[i].get()->getX() < x - 2
				&& objects[i].get()->getY() > 1 && objects[i].get()->getY() < y - 2)
			{

				if (!i)
				{
					// Head moving
					tempX = objects[i].get()->getX();
					tempY = objects[i].get()->getY();

					map[objects[i].get()->getX()][objects[i].get()->getY()] = ' ';

					if (objects[i].get()->getDirection() == Direction::up)
					{
						objects[i].get()->getX() = objects[i].get()->getX() - 1;
					}
					else if (objects[i].get()->getDirection() == Direction::down)
					{
						objects[i].get()->getX() = objects[i].get()->getX() + 1;
					}
					else if (objects[i].get()->getDirection() == Direction::left)
					{
						objects[i].get()->getY() = objects[i].get()->getY() - 1;
					}
					else if (objects[i].get()->getDirection() == Direction::right)
					{
						objects[i].get()->getY() = objects[i].get()->getY() + 1;
					}
				}
				else
				{
					// Body moving
					map[objects[i].get()->getX()][objects[i].get()->getY()] = ' ';
					std::swap(objects[i].get()->getX(), tempX);
					std::swap(objects[i].get()->getY(), tempY);
				}
			}
			else
			{
				gameOver = true;
			}
		}
	}
}

void Engine::checkGameOver(std::thread& keysThread)
{
	if (gameOver)
	{
		TerminateThread(keysThread.native_handle(), 0);
		system("cls");

		std::cout << "######################################################################\n";
		std::cout << "#                                                                    #\n";
		std::cout << "#                                                                    #\n";
		std::cout << "#                       G A M E O V E R                              #\n";
		std::cout << "#                                                                    #\n";
		std::cout << "#                                                                    #\n";
		std::cout << "#                 Y O U R  S C O R E == > ";
		std::cout << score << std::endl;
		std::cout << "#                                                                    #\n";
		std::cout << "#                                                                    #\n";
		std::cout << "#                                                                    #\n";
		std::cout << "#                                                                    #\n";
		std::cout << "#                                                                    #\n";
		std::cout << "#                                                                    #\n";
		std::cout << "#                                                                    #\n";
		std::cout << "#                                                                    #\n";
		std::cout << "#                                                                    #\n";
		std::cout << "#                                                                    #\n";
		std::cout << "#                                                                    #\n";
		std::cout << "#                                                                    #\n";
		std::cout << "######################################################################\n\n";
		std::cout << "Please press any key to exit\n\n";
		system("pause");
		exit(0);
	}
}

void Engine::checkMoving()
{
	// Check for body eating
	for (int i = 1; i < objects.size(); ++i)
	{
		if (objects[0].get()->getX() == objects[i].get()->getX() &&
			objects[0].get()->getY() == objects[i].get()->getY())
		{
			if (objects[i].get()->getCharacter() == '#')
			{
				gameOver = true;
			}
		}
	}

	// Check for eat
	if ((objects[0].get()->getX() == objects[objects.size() - 1].get()->getX() &&
		objects[0].get()->getY() == objects[objects.size() - 1].get()->getY()))
	{
		// Clear map position
		map[objects[objects.size() - 1].get()->getX()][objects[objects.size() - 1].get()->getY()] = ' ';
		// Insetn new head
		Direction direction = objects[0].get()->getDirection();
		objects.insert(objects.begin(), std::make_unique<SnakeHead>(objects[objects.size() - 1].get()->getX(), objects[objects.size() - 1].get()->getY()));
		objects[0].get()->setDirection(direction);
		// Delete eat data
		objects.pop_back();
		// Generate new eat
		generateEat();
		++score;

	}
}

void Engine::generateEat()
{
	int newPosX = 0;
	int newPosY = 0;
	bool correctPosition = false;

	while (!correctPosition)
	{
		newPosX = 3 + (rand() % (Engine::x - 6));
		newPosY = 5 + (rand() % (Engine::y - 10));

		correctPosition = true;

		for (int i = 0; i < objects.size(); ++i)
		{
			if (newPosX == objects[i].get()->getX() && newPosY == objects[i].get()->getY())
			{
				correctPosition = false;
				break;
			}
		}
	}

	objects.push_back(std::make_unique<Eat>(newPosX, newPosY));
}

void Engine::gameMenu()
{
	char choise = '\0';

mainMenu:

	while (choise != '1' && choise != '2' && choise != '3' && choise != '4')
	{
		std::cout << "######################################################################\n";
		std::cout << "#                                                                    #\n";
		std::cout << "#                                                                    #\n";
		std::cout << "#                      M A I N  M E N U                              #\n";
		std::cout << "#                                                                    #\n";
		std::cout << "#                                                                    #\n";
		std::cout << "#                       1 - START GAME                               #\n";
		std::cout << "#                       2 - SETTINGS                                 #\n";
		std::cout << "#                       3 - WARNINGS                                 #\n";
		std::cout << "#                       4 - EXIT                                     #\n";
		std::cout << "#                                                                    #\n";
		std::cout << "#                                                                    #\n";
		std::cout << "#                                                                    #\n";
		std::cout << "#                                                                    #\n";
		std::cout << "#                                                                    #\n";
		std::cout << "#                                                                    #\n";
		std::cout << "#                                                                    #\n";
		std::cout << "#                                                                    #\n";
		std::cout << "#                                                                    #\n";
		std::cout << "######################################################################\n\n";
		std::cout << "Please press number:\n\n";

		choise = _getch();
		system("cls");
	}

	switch (choise)
	{
	case '1':
		break;
	case '2':
		std::cout << "######################################################################\n";
		std::cout << "#                                                                    #\n";
		std::cout << "#                                                                    #\n";
		std::cout << "#                     S E T T I N G S                                #\n";
		std::cout << "#                                                                    #\n";
		std::cout << "#                                                                    #\n";
		std::cout << "#                       W - MOVE UP                                  #\n";
		std::cout << "#                       S - MOVE DOWN                                #\n";
		std::cout << "#                       A - MOVE LEFT                                #\n";
		std::cout << "#                       D - MOVE RIGHT                               #\n";
		std::cout << "#                                                                    #\n";
		std::cout << "#                       Q - EXIT                                     #\n";
		std::cout << "#                                                                    #\n";
		std::cout << "#                                                                    #\n";
		std::cout << "#                                                                    #\n";
		std::cout << "#                                                                    #\n";
		std::cout << "#                                                                    #\n";
		std::cout << "#                                                                    #\n";
		std::cout << "#                                                                    #\n";
		std::cout << "######################################################################\n\n";
		std::cout << "Please press any key to go back\n\n";
		system("pause");
		system("cls");
		choise = '\0';
		goto mainMenu;
	case '3':
		std::cout << "######################################################################\n";
		std::cout << "#                                                                    #\n";
		std::cout << "#                                                                    #\n";
		std::cout << "#                      W A R N I N G S !                             #\n";
		std::cout << "#                                                                    #\n";
		std::cout << "#                                                                    #\n";
		std::cout << "#               Please don't play a lot in this game!                #\n";
		std::cout << "#                                                                    #\n";
		std::cout << "#        This flickering can make you crazy after some time :)       #\n";
		std::cout << "#                                                                    #\n";
		std::cout << "#                                                                    #\n";
		std::cout << "#                                                                    #\n";
		std::cout << "#                                                                    #\n";
		std::cout << "#                                                                    #\n";
		std::cout << "#                                                                    #\n";
		std::cout << "#                                                                    #\n";
		std::cout << "#                                                                    #\n";
		std::cout << "#                                                                    #\n";
		std::cout << "#                                                                    #\n";
		std::cout << "######################################################################\n\n";
		std::cout << "Please press any key to go back\n\n";
		system("pause");
		system("cls");
		choise = '\0';
		goto mainMenu;
	case '4':
		exit(0);
	}

	system("cls");
}