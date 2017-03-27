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

#include <iostream>
#include <SDL.h>
#include <SDL_TTF.h>
#include <SDL_Image.h>
#include <time.h>

#include ".\inc\main.h"
#include ".\inc\Window.h"
#include ".\inc\Player.h"
#include ".\inc\Resources.h"

const int MAP_W = 2000;
const int MAP_H = 2000;

int SCRN_W, SCRN_H;

const int MAX_FPS = 45;
const int ENEMY_SEED = 10;

Resources* Main_Resource;
Window*    Main_Window;

int main(int argc, char* argv[]) {
	PRINT_LEGAL_TERR;
	srand(time(0));
	initSDL();
	
	Main_Window   = new Window();
	Main_Resource = new Resources();
	Main_Window->initWindow();
	
	Player* playerShip = Main_Window->getPlayerShip(); 
	
	uint32_t FPS_Timer = SDL_GetTicks();
	uint32_t moveTimer = SDL_GetTicks();
	SDL_Event event;
	while(true) {
		FPS_Timer = SDL_GetTicks();
		
		if(rand() % (MAX_FPS * ENEMY_SEED))
			Main_Window->createEnemyShip();
		
		Main_Window->moveAll(SDL_GetTicks() - moveTimer);
		moveTimer = SDL_GetTicks();
		
		Main_Window->renderAll();
		
		while(SDL_PollEvent(&event)) {
			if(event.type == SDL_QUIT) {
				quit(0x02);
			}
			
			if(event.type == SDL_KEYUP) {
				switch(event.key.keysym.sym) {
					case SDLK_w:
					case SDLK_s:
						playerShip->setMoving(NOT_MOVING);
					break;
					
					case SDLK_a:
					case SDLK_d:
						playerShip->setTurn(NOT_MOVING);
					break;
					
					case SDLK_SPACE:
						playerShip->fire();
					break;
					
					case SDLK_ESCAPE:
						quit(0x02);
					break;
				}
			}
			
			const Uint8* keystate = SDL_GetKeyboardState(NULL); // Get Keyboard State
			if(keystate[SDL_SCANCODE_S]) // If player is holding down the S Key
				playerShip->setMoving(DOWN_DIRECTION);
			if(keystate[SDL_SCANCODE_W]) // If player is holding down the W Key
				playerShip->setMoving(UP_DIRECTION);
				
			if(keystate[SDL_SCANCODE_A])
				playerShip->setTurn(LEFT_DIRECTION);
			if(keystate[SDL_SCANCODE_D])
				playerShip->setTurn(RIGHT_DIRECTION);
		}
		
		uint32_t frameTicks = SDL_GetTicks() - FPS_Timer; // Get time it took to render frame
		if( frameTicks < 1000.0/MAX_FPS ) // If this was too big
			SDL_Delay( 1000.0/MAX_FPS - frameTicks ); // Wait remainging time
	}
	
	return 0;
}


bool checkCollision(const SDL_Rect& box1, const SDL_Rect& box2) {
	/**
		*Algorithm* \n
		Checks 4 things:
			- If \p box1's left most part is greater than \p box2's right most part.
			- If \p box1's top most part is greater than \p box2's bottom most part.
			- If \p box1's right most part is less than \p box2's left most part.
			- If \p box1's bottom most part is less than \p box2's top most part.
		If any of these are true, then we have a miss and we continue checking the next bullet.
		Else, we have a hit.
		
		@note Actual code goes like this: If any of the points aren't true then we have a hit.\n
		(inverses the condition because we are looking for hits not misses)
	*/
	if(!(
		   box1.x > (box2.x + box2.w)
		|| box1.y > (box2.y + box2.h)
		
		|| box1.x + box1.w < box2.x
		|| box1.y + box1.h < box2.y
	)) return true;
	
	return false;
}


void initSDL() {
	if(SDL_Init(SDL_INIT_VIDEO) < 0) // Init SDL with Video
		EXIT("SDL Init Failed! " << SDL_GetError(), -0x101);
	
	if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) // Set render scaling quality
		EXIT("SDL Scaling Failed! " << SDL_GetError(), -0x101);
		
	int flags = IMG_INIT_PNG | IMG_INIT_JPG; // Init png and jpg/jpeg loading
	if(!(IMG_Init(flags) & flags))
		EXIT("IMG SDL Init Failed! " << IMG_GetError(), -0x101);
	
	if(TTF_Init() < 0) // Init TTF and text rendering
		EXIT("TTF SDL Init Failed! " << TTF_GetError(), -0x101);
	
	// if(Mix_Init(MIX_INIT_OGG) < 0)
		// EXIT("Mixer Init Failed! " << Mix_GetError(), -0x101);
	
	// if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) //Initialize SDL_mixer
		// EXIT("Mixer Init Failed! " << Mix_GetError(), -0x101);
}


void quit(int code) {
	delete Main_Window;
	delete Main_Resource;
	
	IMG_Quit(); // Quit our subsystems
	TTF_Quit();
	SDL_Quit();
	
	exit(code);
}