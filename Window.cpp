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
#include <cmath>

#include ".\inc\main.h"
#include ".\inc\Window.h"
#include ".\inc\Player.h"
#include ".\inc\Bullet.h"
#include ".\inc\Enemy.h"

Window::Window() {
	SDL_DisplayMode mode;
	SDL_GetCurrentDisplayMode(0, &mode); // Get the properties of the screen

	SCRN_H = mode.h - 200;  // Set Window width
	SCRN_W = mode.w - 200; // Set Window width	
	
	if( NULL ==
		(window = SDL_CreateWindow(  // Create our Window
			R_PRGMNAME,  // Window name
			SDL_WINDOWPOS_UNDEFINED,  // Window position (x)
			SDL_WINDOWPOS_UNDEFINED,  // Window position (y)
			SCRN_W, SCRN_H,  // Screen size
			SDL_WINDOW_SHOWN // | SDL_WINDOW_FULLSCREEN // Window flags
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
	this->background = Main_Resource->background;
	camera = {
		(MAP_W - SCRN_W)/2,
		(MAP_H - SCRN_H)/2,
		SCRN_W,
		SCRN_H
	};
}


void Window::moveAll(uint32_t time) {
	playerShip->move(time);
	
	for(auto e : enemyBullets)  e->move(time);
	for(auto e : playerBullets) e->move(time);
	for(auto e : enemyShips)    e->move(time);
	// if(enemyBullets.size() > 0)
		// for(int i = enemyBullets.size() - 1; i >= 0; --i)
			// enemyBullets.at(i)->move(time);
		
	// if(playerBullets.size() > 0)
		// for(int i = playerBullets.size() - 1; i >= 0; --i)
			// playerBullets.at(i)->move(time);
		
	// if(enemyShips.size() > 0)
		// for(int i = enemyShips.size() - 1; i >= 0; --i)
			// enemyShips.at(i)->move(time);
	
}


void Window::renderAll() {
	clear();
	moveCamera();
	renderBackGround();
	
	playerShip->render();
	
	for(auto e : enemyBullets)  e->render();
	for(auto e : playerBullets) e->render();
	for(auto e : enemyShips)    e->render();
	
	
	SDL_RenderPresent(renderer);
}


void Window::clear() {
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF); // Black
	SDL_RenderClear(renderer);
}


void Window::createEnemyShip() { 
	enemyShips.push_back(new Enemy());
}


void Window::moveCamera() {
	playerShip->centerCamOverUs(camera.x, camera.y);

	//Keep the camera in bounds
	if(camera.x < 0)
		camera.x = 0;
	
	if(camera.y < 0)
		camera.y = 0;
	
	if(camera.x + camera.w > MAP_W)
		camera.x = MAP_W - camera.w;
	
	if(camera.y + camera.h > MAP_H)
		camera.y = MAP_H - camera.h;
}


void Window::renderBackGround() {
	int BG_w, BG_h;
	SDL_QueryTexture(background, NULL, NULL, &BG_w, &BG_h);
	//x_f = (ceil(((double)camera.x)/BG_w) * BG_w) - (camera.x + camera.w); 
	SDL_Rect BG_Pos = {
		0,
		0,
		BG_w,
		BG_h
	};
	
	for(
		BG_Pos.x = ((camera.x/BG_w) * BG_w) - camera.x;
		BG_Pos.x < (camera.x + camera.w);
		BG_Pos.x += BG_w
	) {
		for(
			BG_Pos.y = ((camera.y/BG_h) * BG_h) - camera.y;
			BG_Pos.y < (camera.y + camera.h);
			BG_Pos.y += BG_h
		) {
			SDL_RenderCopy(
				this->renderer,
				this->background,
				NULL,
				&BG_Pos
			);
		}
	}	
}


void Window::removeThings() {
	for(auto tmpThing : thingsToRemove) {
		for(unsigned jj = 0; jj < enemyBullets.size(); ++jj) {
			if(tmpThing == enemyBullets[jj]) {
				delete enemyBullets[jj];
				enemyBullets.erase(enemyBullets.begin() + jj);
			}
		}
	
		for(unsigned jj = 0; jj < playerBullets.size(); ++jj) {
			if(tmpThing == playerBullets[jj]) {
				delete playerBullets[jj];
				playerBullets.erase(playerBullets.begin() + jj);
			}
		}
		
		for(unsigned jj = 0; jj < enemyShips.size(); ++jj) {
			if(tmpThing == enemyShips[jj]) {
				delete enemyShips[jj];
				enemyShips.erase(enemyShips.begin() + jj);
			}
		}
	}
	
	thingsToRemove.clear();
}