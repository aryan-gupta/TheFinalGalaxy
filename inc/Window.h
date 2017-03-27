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
 * @date			2017-03-26 (YYYY-MM-DD)
 * @fversion		1.0.0
 * @description 	
 * =============================================================================
 */

#ifndef WINDOW_H_INC
#define WINDOW_H_INC

#include <vector>
#include <SDL.h>
#include <stdint.h>

#include ".\main.h"

class Ship;
class Player;
class Bullet;
class Enemy;

extern int SCRN_W;
extern int SCRN_H;

class Window {
public:
	Window();
	~Window();
	
	void initWindow();
	
	void moveAll(uint32_t time);
	void renderAll();
	void createEnemyShip();
	
	inline SDL_Window* getWindow();
	inline SDL_Renderer* getRenderer();
	inline Player* getPlayerShip();
	inline std::vector<Bullet*>& getEnemyBullets();
	inline void addPlayerBullet(Bullet* bullet);
protected:
	SDL_Window* window;     ///< Stores our main Window
	SDL_Renderer* renderer; ///< Stores our main renderer
	
	std::vector<Ship*> enemyShips;
	std::vector<Bullet*> enemyBullets;
	std::vector<Bullet*> playerBullets;
	
	Player* playerShip;
private:
	void clear();
	void renderAllBullets();
	void moveAllBullets(uint32_t time);
};



inline
SDL_Window* Window::getWindow()
	{ return window; }

inline
SDL_Renderer* Window::getRenderer()
	{ return renderer; }

inline
Player* Window::getPlayerShip()
	{ return playerShip; }

inline
std::vector<Bullet*>& Window::getEnemyBullets() 
	{ return enemyBullets; }
	
inline
void Window::addPlayerBullet(Bullet* bullet)
	{ playerBullets.push_back(bullet); }
	
#endif