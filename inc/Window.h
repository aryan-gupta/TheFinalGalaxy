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
// Class Forward Declarations
class Ship;
class Player;
class Bullet;
class Enemy;

extern int SCRN_W; ///< The width of the screen
extern int SCRN_H; ///< The height of the screen

/// @brief Our window class
/// This class holds all of our window information, is used for rendering,
/// and more
class Window {
public:
	Window();
	~Window();
	
	/// @brief initializes all the variables in our window
	/// The variables aren't done in the constructor because many of the
	/// variables used in this class need to be accessed after the main window 
	/// is created, but after the window is set up
	void initWindow();
	
	void moveAll(uint32_t time); ///< Moves all the objects on the screen @sa Thing::render()
	void renderAll(); ///< Renders all of the objects on the screen
	
	void createEnemyShip(); ///< Creates an \ref Enemy ship
	
	void moveCamera(); ///< Moves the camera respect the \ref Player's Movement
	
	void renderBackGround(); ///< Renders the background respect to the camera
	
	inline SDL_Rect getCamera();
	inline SDL_Window* getWindow();     ///< Get the current Window
	inline SDL_Renderer* getRenderer(); ///< Get the current Window's renderer
	inline Player* getPlayerShip();     ///< Get the Player's Ship
	inline std::vector<Bullet*>& getEnemyBullets(); ///< Get the enemy's Bullet
	inline void addPlayerBullet(Bullet* bullet);    ///< Add a Player's bullet
protected:
	SDL_Window* window;     ///< Stores our main Window
	SDL_Renderer* renderer; ///< Stores our main renderer
	
	SDL_Texture* background; ///< The background texture, Points to texture in \ref Resources
	
	SDL_Rect camera; ///< Stores the location of the camera respect to MAP height and width
	
	std::vector<Ship*> enemyShips;      ///< All the enemy ships
	std::vector<Bullet*> enemyBullets;  ///< All the enemy's \ref Bullet
	std::vector<Bullet*> playerBullets; ///< All the player's \ref Bullet
	
	Player* playerShip; /// The \ref Player's Ship
private:
	void clear(); ///< clear the renderer
};

inline
SDL_Rect Window::getCamera()
	{ return camera; }

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