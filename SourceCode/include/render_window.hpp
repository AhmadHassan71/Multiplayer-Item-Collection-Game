#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "Object.hpp"

class RenderWindow
{
public:
	RenderWindow(const char *p_title, int p_w, int p_h);
	SDL_Texture *loadTexture(const char *p_filePath);
	int getRefreshRate();
	void cleanUp();
	void clear();
	void render(Object &);
	void render_str(std::string score);

	void display();


	SDL_Window *window;
	SDL_Renderer *renderer;
};

RenderWindow::RenderWindow(const char *p_title, int p_w, int p_h)
	: window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}
int RenderWindow::getRefreshRate()
{
	int displayIndex = SDL_GetWindowDisplayIndex(window);
	SDL_DisplayMode mode;
	SDL_GetCurrentDisplayMode(displayIndex, &mode);
	return mode.refresh_rate;
}
SDL_Texture *RenderWindow::loadTexture(const char *p_filePath)
{
	SDL_Texture *texture = NULL;
	texture = IMG_LoadTexture(renderer, p_filePath);

	if (texture == NULL)
		std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;

	return texture;
}

void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(window);
}

void RenderWindow::clear()
{
	SDL_RenderClear(renderer);
}

void RenderWindow::render(Object &p_object)
{
	SDL_Rect srcRect;
	srcRect.x = p_object.getCurrentFrame().x;
	srcRect.y = p_object.getCurrentFrame().y;
	srcRect.w = p_object.getCurrentFrame().w;
	srcRect.h = p_object.getCurrentFrame().h;

	SDL_Rect destRect;
	destRect.x = p_object.getPos().x*4;
	destRect.y = p_object.getPos().y*4;
	destRect.w = p_object.getCurrentFrame().w*4;
	destRect.h = p_object.getCurrentFrame().h*4;

	SDL_RenderCopy(renderer, p_object.getTexture(), &srcRect, &destRect);
}

void RenderWindow::render_str(std::string score)
{
	TTF_Init();
    TTF_Font* font = TTF_OpenFont("arial.ttf", 50);

	SDL_Rect textbox = {0,0,0,0};
	SDL_Color textColor = {255, 255, 255};
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, score.c_str(), textColor);


	SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	int w, h;
    SDL_QueryTexture(message, NULL, NULL, &w, &h);

    // Update the size and location of the text box based on the texture size
    textbox.w = w;
    textbox.h = h;
    textbox.x = 5; // center horizontally
    textbox.y = 10;

    

    // Copy the texture onto the renderer
    SDL_RenderCopy(renderer, message, NULL, &textbox);
	
}

void RenderWindow::display()
{
	SDL_RenderPresent(renderer);
}