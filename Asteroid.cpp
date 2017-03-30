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

#include <vector>
using std::vector;

#include ".\inc\main.h"
#include ".\inc\Asteroid.h"
#include ".\inc\Resources.h"
#include ".\inc\Bullet.h"
#include ".\inc\Window.h"


Asteroid::Asteroid() : Thing(SPRITE_SHEET_1, rand() % 360){
	clipping = Main_Resource->clip_astroids[rand() % 20];
	position = SDL_Rect {
		rand() % (MAP_W - clipping.w),
		rand() % (MAP_H - clipping.h),
		clipping.w,
		clipping.h
	};
	xPosition = position.x;
	yPosition = position.y;
}


void Asteroid::checkHit() {
	for(auto b : Main_Window->getPlayerBullets()) {
		if(checkCollision(b->getPosition(), this->position)) {
			//b->explode();
			this->explode();
		}
	}
	
	for(auto b : Main_Window->getEnemyBullets()) {
		if(checkCollision(b->getPosition(), this->position)) {
			//b->explode();
			this->explode();
		}
	}
}

SDL_Rect& Asteroid::getPosition() {
	return position;
}