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
**/

#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <iostream>
#include <SDL.h>
// Forward Declarations
struct Resources;
class Window;

extern const int MAP_W;   ///< The entire map width
extern const int MAP_H;   ///< The entire map height
extern const int MAX_FPS; ///< The max FPS of the game

extern Resources* Main_Resource; ///< All the resources of the game
extern Window*    Main_Window;   ///< The Main Window

/// @brief General Directions on the Map
enum Direction {
	UP_DIRECTION,    ///< Up Direction
	DOWN_DIRECTION,  ///< Down Direction
	LEFT_DIRECTION,  ///< Left Direction
	RIGHT_DIRECTION, ///< Right Direction
	
	TOTAL_DIRECTION, ///< Total Directions
	NOT_MOVING       ///< Not Moving
};

/// @brief Program Entry Point
/// @param [in] argc `int` The number of command line arguments
/// @param [in] argv `char**` The command line arguments
int main(int argc, char* argv[]);

/// @brief Checks a collision between 2 SDL_Rects
/// @param [in] `SDL_Rect` First box to check against
/// @param [in] `SDL_Rect` Second box to check against
/// @return `bool` if they collide or not
/// @retval TRUE They collide
/// @retval FALSE They don't collide
bool checkCollision(const SDL_Rect& box1, const SDL_Rect& box2);

void initSDL(); ///< Initiates SDL and other sub-systems

void quit(int code); ///< Closes Subsystems, cleans up and exits with exit code

#endif // MAIN_H_INCLUDED