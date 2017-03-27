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

struct Resources;
class Window;

enum Direction {
	UP_DIRECTION,
	DOWN_DIRECTION,
	
	LEFT_DIRECTION,
	RIGHT_DIRECTION,
	
	TOTAL_DIRECTION,
	
	NOT_MOVING
};

enum SpriteSheets {
	SPRITE_SHEET_1,
	SPRITE_SHEET_2,
	SPRITE_SHEET_3,
	
	TOTAL_SPRITE_SHEETS
};

enum Shooters {
	PLAYER_SHIP,
	ENEMY_SHIP
};


extern const int MAP_W;
extern const int MAP_H;
extern const int MAX_FPS;

extern Resources* Main_Resource;
extern Window*    Main_Window;

int main(int argc, char* argv[]);

bool checkCollision(const SDL_Rect& box1, const SDL_Rect& box2);

void initSDL();

void quit(int code);

#endif // MAIN_H_INCLUDED