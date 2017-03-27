/* 
 * Copyright (c) 2017 The Gupta Empire - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 *
 * Written by Aryan Gupta <me@theguptaempire.net>
 * 
 * =============================================================================
 * @author 			Aryan Gupta
 * @project 		
 * @title 			
 * @date			(YYYY-MM-DD)
 * @fversion		1.0.0
 * @description 	
 * =============================================================================
 */
#include "info.h"

#include <SDL.h>

#include ".\inc\main.h"
#include ".\inc\Window.h"
#include ".\inc\Player.h"
#include ".\inc\Bullet.h"
//#include ".\inc\Enemy.h"

Window::Window() {
	SDL_DisplayMode mode;
	SDL_GetCurrentDisplayMode(0, &mode); // Get the properties of the screen

	SCRN_H = mode.h;  // Set Window width
	SCRN_W = mode.w; // Set Window width	
	
	if( NULL ==
		(window = SDL_CreateWindow(  // Create our Window
			R_PRGMNAME,  // Window name
			SDL_WINDOWPOS_UNDEFINED,  // Window position (x)
			SDL_WINDOWPOS_UNDEFINED,  // Window position (y)
			SCRN_W, SCRN_H,  // Screen size
			SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN // Window flags
		))
	) EXIT("SDL Create Window Failed! " << SDL_GetError(), -0x101);
	
	if( NULL ==
		(renderer = SDL_CreateRenderer( // Create our main renderer
			window, -1,
			SDL_RENDERER_ACCELERATED // Renderer flags
		))
	) EXIT("SDL Create Renderer Failed! " << SDL_GetError(), -0x101);
	
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}


Window::~Window() {
	
}


void Window::initWindow() {
	playerShip = new Player();
}


void Window::moveAll(uint32_t time) {
	playerShip->move(time);
	moveAllBullets(time);
}


void Window::renderAll() {
	clear();
	
	playerShip->render();
	renderAllBullets();
	
	SDL_RenderPresent(renderer);
}


void Window::clear() {
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF); // Black
	SDL_RenderClear(renderer);
}


void Window::renderAllBullets() {
	for(auto b : enemyBullets)
		b->render();
	
	for(auto b : playerBullets)
		b->render();
}


void Window::moveAllBullets(uint32_t time) {
	for(auto b : enemyBullets)
		b->move(time);
	for(auto b : playerBullets)
		b->move(time);
}

void Window::createEnemyShip() { 
	//enemyShips.push_back(new Enemy());
}