#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <pthread.h>
#include "include/render_window.hpp"
#include "include/Object.hpp"
#include "include/Utility.hpp"
#include "include/threadFun.hpp"

using namespace std;

int findSizeOfBoard(int RollNum, int LastDigit);
void gameDisplay();

int main(int argc, char *args[])
{

	gameDisplay();
	SDL_Quit();

	return 0;
}

int findSizeOfBoard(int RollNum, int LastDigit) // finds out "n" or the size of matrix
{

	int sizeNum = (int)randomizer(10, 99);
	sizeNum *= LastDigit;
	RollNum /= sizeNum;

	RollNum %= 25;
	sizeNum = RollNum;

	if (sizeNum < 10)
		sizeNum += 15;

	return sizeNum;
}

void gameDisplay()
{
	int RollNum = 403;
	int LastDigit = (RollNum % 100);

	int W_Board = findSizeOfBoard(RollNum, LastDigit);
	int H_Board = findSizeOfBoard(RollNum, LastDigit);

	int GameBoard[H_Board][W_Board];

	pid_t p1, p2, p3;
	pthread_t thr_p1, thr_p2, thr_p3;
	pthread_attr_t a1, a2, a3;
	pthread_attr_init(&a1);
	pthread_attr_init(&a2);
	pthread_attr_init(&a3);
	pthread_attr_setdetachstate(&a1, PTHREAD_CREATE_JOINABLE);
	pthread_attr_setdetachstate(&a2, PTHREAD_CREATE_JOINABLE);
	pthread_attr_setdetachstate(&a3, PTHREAD_CREATE_JOINABLE);

	if (SDL_Init(SDL_INIT_VIDEO) && TTF_Init() > 0)
		std::cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;

	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;

	RenderWindow window("21i-0403 - Assignemnt2", 1280, 720);

	int windowRefreshRate = window.getRefreshRate();

	// std::cout<<"Refresh rate: "<<windowRefreshRate<<std::endl;
	// for running using cmake
	/*
	SDL_Texture *player1 = window.loadTexture("src/img/sprites/p1.png");
	SDL_Texture *player2 = window.loadTexture("src/img/sprites/p2.png");
	SDL_Texture *player3 = window.loadTexture("src/img/sprites/p3.png");

	SDL_Texture *bkg = window.loadTexture("src/img/grass.png");
	SDL_Texture *i1 = window.loadTexture("src/img/items/axe.png");
	SDL_Texture *i2 = window.loadTexture("src/img/items/sword.png");
	SDL_Texture *i3 = window.loadTexture("src/img/items/helm.png");
	SDL_Texture *i4 = window.loadTexture("src/img/items/goldhelm.png");
	SDL_Texture *PauseMenu = window.loadTexture("src/img/pause.png");
*/
	// for running on terminal uncomment the comment below and comment the code above

	SDL_Texture *player1 = window.loadTexture("img/sprites/p1.png");
	SDL_Texture *player2 = window.loadTexture("img/sprites/p2.png");
	SDL_Texture *player3 = window.loadTexture("img/sprites/p3.png");

	SDL_Texture *bkg = window.loadTexture("img/grass.png");
	SDL_Texture *i1 = window.loadTexture("img/items/axe.png");
	SDL_Texture *i2 = window.loadTexture("img/items/sword.png");
	SDL_Texture *i3 = window.loadTexture("img/items/helm.png");
	SDL_Texture *i4 = window.loadTexture("img/items/goldhelm.png");
	SDL_Texture *PauseMenu = window.loadTexture("img/pause.png");

	string score1 = "Player 1";
	string score2 = "Player 2";
	string score3 = "Player 3";
	TTF_Font *font = TTF_OpenFont("src/fonts/arial.TTF", 24);
	SDL_Color color = {255, 255, 255, 255};

	std::vector<Object> board = {Object(Vector2f(0, 0), bkg), Object(Vector2f(30, 0), bkg), Object(Vector2f(60, 0), bkg),
								 Object(Vector2f(90, 0), bkg), Object(Vector2f(120, 0), bkg), Object(Vector2f(150, 0), bkg),
								 Object(Vector2f(180, 0), bkg), Object(Vector2f(210, 0), bkg), Object(Vector2f(240, 0), bkg),
								 Object(Vector2f(270, 0), bkg), Object(Vector2f(300, 0), bkg),
								 Object(Vector2f(0, 30), bkg), Object(Vector2f(30, 30), bkg), Object(Vector2f(60, 30), bkg),
								 Object(Vector2f(90, 30), bkg), Object(Vector2f(120, 30), bkg), Object(Vector2f(150, 30), bkg),
								 Object(Vector2f(180, 30), bkg), Object(Vector2f(210, 30), bkg), Object(Vector2f(240, 30), bkg),
								 Object(Vector2f(270, 30), bkg), Object(Vector2f(300, 30), bkg),
								 Object(Vector2f(0, 60), bkg), Object(Vector2f(30, 60), bkg), Object(Vector2f(60, 60), bkg),
								 Object(Vector2f(90, 60), bkg), Object(Vector2f(120, 60), bkg), Object(Vector2f(150, 60), bkg),
								 Object(Vector2f(180, 60), bkg), Object(Vector2f(210, 60), bkg), Object(Vector2f(240, 60), bkg),
								 Object(Vector2f(270, 60), bkg), Object(Vector2f(300, 60), bkg),
								 Object(Vector2f(0, 90), bkg), Object(Vector2f(30, 90), bkg), Object(Vector2f(60, 90), bkg),
								 Object(Vector2f(90, 90), bkg), Object(Vector2f(120, 90), bkg), Object(Vector2f(150, 90), bkg),
								 Object(Vector2f(180, 90), bkg), Object(Vector2f(210, 90), bkg), Object(Vector2f(240, 90), bkg),
								 Object(Vector2f(270, 90), bkg), Object(Vector2f(300, 90), bkg),
								 Object(Vector2f(0, 120), bkg), Object(Vector2f(30, 120), bkg), Object(Vector2f(60, 120), bkg),
								 Object(Vector2f(90, 120), bkg), Object(Vector2f(120, 120), bkg), Object(Vector2f(150, 120), bkg),
								 Object(Vector2f(180, 120), bkg), Object(Vector2f(210, 120), bkg), Object(Vector2f(240, 120), bkg),
								 Object(Vector2f(270, 120), bkg), Object(Vector2f(300, 120), bkg),
								 Object(Vector2f(0, 150), bkg),
								 Object(Vector2f(30, 150), bkg), Object(Vector2f(60, 150), bkg), Object(Vector2f(90, 150), bkg),
								 Object(Vector2f(120, 150), bkg), Object(Vector2f(150, 150), bkg), Object(Vector2f(180, 150), bkg),
								 Object(Vector2f(210, 150), bkg), Object(Vector2f(240, 150), bkg), Object(Vector2f(270, 150), bkg),
								 Object(Vector2f(300, 150), bkg)};

	Object _player1 = {Object(Vector2f(randomizer(0, 30), randomizer(50, 120)), player1)};
	Object _player2 = {Object(Vector2f(randomizer(30, 60), randomizer(0, 120)), player2)};
	Object _player3 = {Object(Vector2f(randomizer(45, 90), randomizer(35, 100)), player3)};

	Object axe = {Object(Vector2f(randomizer(0, 200), randomizer(75, 100)), i1)};
	Object sword = {Object(Vector2f(randomizer(75, 200), randomizer(0, 100)), i2)};
	Object helm = {Object(Vector2f(randomizer(100, 140), randomizer(30, 70)), i3)};
	Object goldhelm = {Object(Vector2f(randomizer(100, 200), randomizer(70, 100)), i4)};
	Object pause_menu = {Object(Vector2f(0, 0), PauseMenu)};
	bool gameRunning = true;

	SDL_Event event;

	const float timeStep = 0.01f; // tickrate of 100ms
	float accumulator = 0.0f;
	float currentTime = utils::hireTime();
	int score[3] = {0};
	bool pause = false;

	while (gameRunning)
	{
		SDL_Texture *__score1 = SDL_CreateTextureFromSurface(window.renderer, TTF_RenderText_Solid(font, score1.c_str(), color));
		SDL_Texture *__score2 = SDL_CreateTextureFromSurface(window.renderer, TTF_RenderText_Solid(font, score2.c_str(), color));
		SDL_Texture *__score3 = SDL_CreateTextureFromSurface(window.renderer, TTF_RenderText_Solid(font, score3.c_str(), color));
		Object _score1 = {Object(Vector2f(10, 5), __score1)};
		Object _score2 = {Object(Vector2f(10, 10), __score2)};
		Object _score3 = {Object(Vector2f(10, 15), __score2)};

		// Working of ticks in game
		int startTicks = SDL_GetTicks();
		float newTime = utils::hireTime();
		float frameTime = newTime - currentTime;
		currentTime = newTime;
		accumulator += frameTime;
		while (accumulator >= timeStep)
		{
			// update
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
					gameRunning = false;
			}
			accumulator -= timeStep;
		}

		const float alpha = accumulator / timeStep;
		// render
		//  Get our controls and events
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				gameRunning = false;

			// std::cout<<"Key pressed"<<std::endl;
			void *obj1 = (void *)_player1;
			void *obj2 = (void *)_player2;
			void *obj3 = (void *)_player3;

			switch (event.key.keysym.sym)
			{
			case SDLK_UP:
				// cout << "UP" << endl;
				pthread_create(&thr_p1, &a1, moveUp, obj1);
				pthread_join(thr_p1, &obj1);
				//_player1.move(0, -30);
				// cout << _player1.getPos().x << _player1.getPos().y << endl;
				if (_player1.getPos().intersects(_player2.getPos()) || _player1.getPos().intersects(_player3.getPos()))
				{
					score[0]--;
					_player1.move(0, -30);
				}
				break;

			case SDLK_DOWN:
				// cout << "DOWN" << endl;

				pthread_create(&thr_p1, &a1, moveDown, obj1);
				pthread_join(thr_p1, &obj1);
				if (_player1.getPos().intersects(_player2.getPos()) || _player1.getPos().intersects(_player3.getPos()))
				{
					score[0]--;
					_player1.move(0, 30);
				}

				//_player1.move(0, 30);
				// cout << _player1.getPos().x << _player1.getPos().y << endl;

				break;
			case SDLK_LEFT:
				pthread_create(&thr_p1, &a1, moveLeft, obj1);
				pthread_join(thr_p1, &obj1);
				if (_player1.getPos().intersects(_player2.getPos()) || _player1.getPos().intersects(_player3.getPos()))
				{
					score[0]--;
					_player1.move(30, 0);
				}

				//_player1.move(-30, 0);
				// cout << _player1.getPos().x << _player1.getPos().y << endl;

				break;
			case SDLK_RIGHT:
				pthread_create(&thr_p1, &a1, moveRight, obj1);
				pthread_join(thr_p1, &obj1);
				if (_player1.getPos().intersects(_player2.getPos()) || _player1.getPos().intersects(_player3.getPos()))
				{
					score[0]--;
					_player1.move(30, 0);
				}

				//_player1.move(30, 0);
				// cout << _player1.getPos().x << _player1.getPos().y << endl;
				break;
			case SDLK_w:

				pthread_create(&thr_p2, &a2, moveUp, obj2);
				pthread_join(thr_p2, &obj2);
				if (_player2.getPos().intersects(_player1.getPos()) || _player2.getPos().intersects(_player3.getPos()))
				{
					score[1]--;
					_player2.move(0, -30);
				}

				// cout << "UP" << endl;
				//_player2.move(0, -30);
				// cout << _player2.getPos().x << _player2.getPos().y << endl;

				break;
			case SDLK_s:
				pthread_create(&thr_p2, &a2, moveDown, obj2);
				pthread_join(thr_p2, &obj2);
				if (_player2.getPos().intersects(_player1.getPos()) || _player2.getPos().intersects(_player3.getPos()))
				{
					score[1]--;
					_player2.move(0, 30);
				}

				// cout << "DOWN" << endl;
				//_player2.move(0, 30);
				// cout << _player2.getPos().x << _player2.getPos().y << endl;

				break;
			case SDLK_a:
				pthread_create(&thr_p2, &a2, moveLeft, obj2);
				pthread_join(thr_p2, &obj2);
				if (_player2.getPos().intersects(_player1.getPos()) || _player2.getPos().intersects(_player3.getPos()))
				{
					score[1]--;
					_player2.move(30, 0);
				}
				//_player2.move(-30, 0);
				// cout << _player2.getPos().x << _player2.getPos().y << endl;

				break;
			case SDLK_d:
				pthread_create(&thr_p2, &a2, moveRight, obj2);
				pthread_join(thr_p2, &obj2);
				if (_player2.getPos().intersects(_player1.getPos()) || _player2.getPos().intersects(_player3.getPos()))
				{
					score[1]--;
					_player2.move(-30, 0);
				}
				//_player2.move(30, 0);
				// cout << _player2.getPos().x << _player2.getPos().y << endl;
				break;
			case SDLK_i:
				pthread_create(&thr_p3, &a3, moveUp, obj3);
				pthread_join(thr_p3, &obj3);
				if (_player3.getPos().intersects(_player2.getPos()) || _player3.getPos().intersects(_player1.getPos()))
				{
					score[2]--;
					_player3.move(0, -30);
				}
				// cout << "UP" << endl;
				//_player3.move(0, -30);
				// cout << _player2.getPos().x << _player2.getPos().y << endl;

				break;
			case SDLK_k:
				pthread_create(&thr_p3, &a3, moveDown, obj3);
				pthread_join(thr_p3, &obj3);
				if (_player3.getPos().intersects(_player2.getPos()) || _player3.getPos().intersects(_player1.getPos()))
				{
					score[2]--;
					_player3.move(0, 30);
				}
				// cout << "DOWN" << endl;
				//_player3.move(0, 30);
				// cout << _player2.getPos().x << _player2.getPos().y << endl;

				break;
			case SDLK_j:
				pthread_create(&thr_p3, &a3, moveLeft, obj3);
				pthread_join(thr_p3, &obj3);
				if (_player3.getPos().intersects(_player2.getPos()) || _player3.getPos().intersects(_player1.getPos()))
				{
					score[2]--;
					_player3.move(30, 0);
				}
				//_player3.move(-30, 0);
				// cout << _player2.getPos().x << _player2.getPos().y << endl;

				break;
			case SDLK_l:
				pthread_create(&thr_p3, &a3, moveRight, obj3);
				pthread_join(thr_p3, &obj3);
				if (_player3.getPos().intersects(_player2.getPos()) || _player3.getPos().intersects(_player1.getPos()))
				{
					score[2]--;
					_player3.move(-30, 0);
				}
				//_player3.move(30, 0);
				// cout << _player2.getPos().x << _player2.getPos().y << endl;
				break;
			case SDLK_ESCAPE:
				gameRunning = false;
			case SDLK_SPACE:
			case SDLK_p:
				pause = !pause;
				break;
			}
		}
		if (!pause)
		{

			if (_player1.getPos().intersects(axe.getPos()))
			{
				score[0] += 10;
				axe.setPos(randomizer(25, 200), randomizer(20, 40));
				// window.render(axe);
			}
			if (_player1.getPos().intersects(sword.getPos()))
			{
				score[0] += 20;
				sword.setPos(randomizer(75, 250), randomizer(0, 20));
				// window.render(sword);
			}
			if (_player1.getPos().intersects(helm.getPos()))
			{
				score[0] += 30;
				helm.setPos(randomizer(100, 150), randomizer(30, 70));
				// window.render(helm);
			}
			if (_player1.getPos().intersects(goldhelm.getPos()))
			{
				score[0] += 50;
				goldhelm.setPos(randomizer(100, 200), randomizer(70, 100));
				// window.render(goldhelm);
			}

			if (_player2.getPos().intersects(axe.getPos()))
			{
				score[1] += 10;
				axe.setPos(randomizer(25, 200), randomizer(20, 40));
				// window.render(axe);
			}
			if (_player2.getPos().intersects(sword.getPos()))
			{
				score[1] += 20;
				sword.setPos(randomizer(75, 250), randomizer(0, 20));
				// window.render(sword);
			}
			if (_player2.getPos().intersects(helm.getPos()))
			{
				score[1] += 30;
				helm.setPos(randomizer(100, 150), randomizer(30, 70));
				// window.render(helm);
			}
			if (_player2.getPos().intersects(goldhelm.getPos()))
			{
				score[1] += 50;
				goldhelm.setPos(randomizer(100, 200), randomizer(70, 100));
				// window.render(goldhelm);
			}
			if (_player3.getPos().intersects(axe.getPos()))
			{
				score[2] += 10;
				axe.setPos(randomizer(25, 200), randomizer(20, 40));
				// window.render(axe);
			}
			if (_player3.getPos().intersects(sword.getPos()))
			{
				score[2] += 20;
				sword.setPos(randomizer(75, 250), randomizer(0, 20));
				// window.render(sword);
			}
			if (_player3.getPos().intersects(helm.getPos()))
			{
				score[2] += 30;
				helm.setPos(randomizer(100, 150), randomizer(30, 70));
				// window.render(helm);
			}
			if (_player3.getPos().intersects(goldhelm.getPos()))
			{
				score[2] += 50;
				goldhelm.setPos(randomizer(100, 200), randomizer(70, 100));
				// window.render(goldhelm);
			}

			score1 = "Player 1 " + std::to_string(score[0]);
			score2 = "Player 2 " + std::to_string(score[1]);
			score3 = "Player 3 " + std::to_string(score[2]);
			__score1 = SDL_CreateTextureFromSurface(window.renderer, TTF_RenderText_Solid(font, score1.c_str(), color));
			__score2 = SDL_CreateTextureFromSurface(window.renderer, TTF_RenderText_Solid(font, score2.c_str(), color));
			__score3 = SDL_CreateTextureFromSurface(window.renderer, TTF_RenderText_Solid(font, score3.c_str(), color));

			/*std::cout << "\nscores" << std::endl;
			std::cout << score1 << std::endl;
			std::cout << score2 << std::endl;
			std::cout << score3 << std::endl;*/

			window.render(_score1);
			window.render(_score2);
			window.render(_score3);

			if (_player2.getPos().x < 0)
				_player2.move(20, 0);

			if (_player2.getPos().x >= 295)
				_player2.move(-20, 0);

			if (_player2.getPos().y < 0)
				_player2.move(0, 20);

			if (_player2.getPos().y >= 140)
				_player2.move(0, -20);

			if (_player1.getPos().x < 0)
				_player1.move(20, 0);

			if (_player1.getPos().x >= 295)
				_player1.move(-20, 0);

			if (_player1.getPos().y < 0)
				_player1.move(0, 20);

			if (_player1.getPos().y >= 140)
				_player1.move(0, -20);

			if (_player3.getPos().x < 0)
				_player3.move(20, 0);

			if (_player3.getPos().x >= 295)
				_player3.move(-20, 0);

			if (_player3.getPos().y < 0)
				_player3.move(0, 20);

			if (_player3.getPos().y >= 140)
				_player3.move(0, -20);

			for (Object &o : board)
			{
				window.render(o);
			}
			window.render(_player1);
			window.render(_player2);
			window.render(_player3);

			window.render(axe);
			window.render(sword);
			window.render(helm);
			window.render(goldhelm);
			window.render(_score1);
			window.render(_score2);
			window.render(_score3);
			// std::cout<<"Util hire time in secs : "<<utils::hireTime()<<std::endl;
			window.display();
		}
		else
		{
			window.render(pause_menu);
			window.display();
		}

		int frameTicks = SDL_GetTicks() - startTicks;
		if (frameTicks < 300 / window.getRefreshRate())
		{
			SDL_Delay(300 / window.getRefreshRate() - frameTicks);
		}
	}

	window.cleanUp();
}
