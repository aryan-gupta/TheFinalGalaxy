/** 
 * Copyright (c) 2017 The Gupta Empire - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 *
 * Written by Aryan Gupta <me@theguptaempire.net>
 * 
 * =============================================================================
 * @author 			Aryan Gupta
 * @project 		
 * @file 			
 * @date			2017-03-21 (YYYY-MM-DD)
 * @version		2.0.0
 * @brief 	
 * =============================================================================
**/
#include "info.h"

#include <iostream>
#include <SDL_TTF.h>

#include ".\inc\main.h"
#include ".\inc\Resources.h"
#include ".\inc\Window.h"

const char* SPRITE_RES[] = {
	"..\\res\\Sheets\\sheet_1.png",
	"..\\res\\Sheets\\sheet_2.png",
	"..\\res\\Sheets\\sheet_3.png"
};

const char* EXPLOSION_RES    = "..\\res\\other\\explosion.png";
const char* BACKGROUND_IMAGE = "..\\res\\other\\background.png";
const char* MAIN_FONT        = "..\\res\\other\\main_font.ttf";
const char* BRIEF_FONT       = "..\\res\\other\\brief_font.ttf";
const char* TITLE_FONT       = "..\\res\\other\\title_font.ttf";
const char* LIFE_IMAGE       = "..\\res\\other\\life.png";

const char* FIRE_AUDIO       = "..\\res\\ogg\\sfx_laser1.wav";


Resources::Resources() {
	explosion   = load(EXPLOSION_RES);
	background  = load(BACKGROUND_IMAGE);
	healthHeart = load(LIFE_IMAGE);
	
	//fire = Mix_LoadWAV(FIRE_AUDIO);;
	
	mainFont = TTF_OpenFont(MAIN_FONT, 30); // Load the font
	if(mainFont == NULL)
		EXIT("Font Opening Failed" << TTF_GetError(), -0x20A);
	
	briefFont = TTF_OpenFont(BRIEF_FONT, 19); // Load the font
	if(briefFont == NULL)
		EXIT("Font Opening Failed" << TTF_GetError(), -0x20A);
	
	titleFont = TTF_OpenFont(TITLE_FONT, 75); // Load the font
	if(titleFont == NULL)
		EXIT("Font Opening Failed" << TTF_GetError(), -0x20A);
	
	spriteSheets = new SDL_Texture*[3];
	for(int i = 0; i < 3; ++i) {
		spriteSheets[i] = load(SPRITE_RES[i]);
	}
	
	// ==== SHEET 1 ====
	clip_enemyShips = new SDL_Rect[5];
	clip_enemyShips[0] = SDL_Rect{423, 728,  93, 84};
	clip_enemyShips[1] = SDL_Rect{120, 604, 104, 84};
	clip_enemyShips[2] = SDL_Rect{144, 156, 103, 84};
	clip_enemyShips[3] = SDL_Rect{518, 325,  82, 84};
	clip_enemyShips[4] = SDL_Rect{346, 150,  97, 84};
	
	clip_astroids = new SDL_Rect[20];
	clip_astroids[ 0] = SDL_Rect{224, 664, 101,  84}; // BIG ASTROID BROWN
	clip_astroids[ 1] = SDL_Rect{  0, 520, 120,  98}; // BIG ASTROID BROWN
	clip_astroids[ 2] = SDL_Rect{518, 810,  89,  82}; // BIG ASTROID BROWN
	clip_astroids[ 3] = SDL_Rect{327, 452,  98,  96}; // BIG ASTROID BROWN
	clip_astroids[ 4] = SDL_Rect{224, 748, 101,  84}; // BIG ASTROID GREY
	clip_astroids[ 5] = SDL_Rect{  0, 618, 120,  98}; // BIG ASTROID GREY
	clip_astroids[ 6] = SDL_Rect{516, 728,  89,  82}; // BIG ASTROID GREY
	clip_astroids[ 7] = SDL_Rect{327, 548,  98,  96}; // BIG ASTROID GREY
	clip_astroids[ 8] = SDL_Rect{651, 447,  43,  43}; // MEDIUM ASTROID BROWN
	clip_astroids[ 9] = SDL_Rect{237, 452,  45,  40}; // MEDIUM ASTROID BROWN
	clip_astroids[10] = SDL_Rect{674, 219,  43,  43}; // MEDIUM ASTROID GREY
	clip_astroids[11] = SDL_Rect{282, 452,  45,  40}; // MEDIUM ASTROID GREY
	clip_astroids[12] = SDL_Rect{406, 262,  28,  28}; // SMALL ASTROID BROWN
	clip_astroids[13] = SDL_Rect{396, 413,  29,  26}; // SMALL ASTROID BROWN
	clip_astroids[14] = SDL_Rect{406, 234,  28,  28}; // SMALL ASTROID GREY
	clip_astroids[15] = SDL_Rect{778, 587,  29,  26}; // SMALL ASTROID GREY
	clip_astroids[16] = SDL_Rect{346, 814,  18,  18}; // TINY ASTROID BROWN
	clip_astroids[17] = SDL_Rect{399, 814,  16,  15}; // TINY ASTROID BROWN
	clip_astroids[18] = SDL_Rect{364, 814,  18,  18}; // TINY ASTROID GREY
	clip_astroids[19] = SDL_Rect{602, 646,  16,  15}; // TINY ASTROID GREY
	
	clip_powerup = new SDL_Rect[13];
	clip_powerup[ 0] = SDL_Rect{810, 467, 19, 30}; // FIRE_POWERUP_1
	clip_powerup[ 1] = SDL_Rect{810, 837, 19, 30};
	clip_powerup[ 2] = SDL_Rect{809, 437, 19, 30};
	clip_powerup[ 3] = SDL_Rect{674, 262, 22, 21}; // HEALTH_POWERUP_1
	clip_powerup[ 4] = SDL_Rect{573, 989, 22, 21};
	clip_powerup[ 5] = SDL_Rect{222, 108, 22, 21};
	clip_powerup[ 6] = SDL_Rect{222, 129, 22, 21};
	clip_powerup[ 7] = SDL_Rect{797, 143, 30, 30}; // SHIELD_POWERUPS
	clip_powerup[ 8] = SDL_Rect{778, 824, 30, 30};
	clip_powerup[ 9] = SDL_Rect{797, 113, 30, 30};
	clip_powerup[10] = SDL_Rect{778, 794, 31, 30}; // BEAM POWERUP
	clip_powerup[11] = SDL_Rect{778, 557, 31, 30};
	clip_powerup[12] = SDL_Rect{778, 527, 31, 30};
	
	// ===== SHEET 2 =====
	clip_playerShips = new SDL_Rect[3];
	clip_playerShips[0] = SDL_Rect{480, 1045, 106, 80};
	clip_playerShips[1] = SDL_Rect{276,  323, 101, 74};
	clip_playerShips[2] = SDL_Rect{567,  191, 100, 94};
	
	clip_bullets = new SDL_Rect[2];
	clip_bullets[0] = SDL_Rect{1093, 995, 20, 35};
	clip_bullets[1] = SDL_Rect{1092, 116, 20, 35};
	
	clip_shield = SDL_Rect{0, 156, 144, 137};
}


Resources::~Resources() {
	for(int i = 0; i < 3; ++i) {
		SDL_DestroyTexture(spriteSheets[i]); spriteSheets[i] = NULL;
	}
	delete[] spriteSheets;
	
	SDL_DestroyTexture(explosion);   explosion = NULL;
	SDL_DestroyTexture(healthHeart); healthHeart = NULL;
	TTF_CloseFont(mainFont);         mainFont = NULL;
	
	delete[] clip_enemyShips;
	delete[] clip_astroids;
	delete[] clip_powerup;
	
	delete[] clip_playerShips;
	delete[] clip_bullets;
	
}


SDL_Texture* Resources::load(const char* file) {
	SDL_Surface* tmp = IMG_Load(file);
		
	if(tmp == NULL)
		EXIT("Could not load " << file << IMG_GetError(), -0x101)
	
	return SDL_CreateTextureFromSurface ( // Set the Player's texture
		Main_Window->getRenderer(),
		tmp
	);
}