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
#include <cmath>

#include ".\inc\main.h"
#include ".\inc\Bullet.h"
#include ".\inc\Resources.h"
#include ".\inc\Window.h"

Bullet::Bullet(double direction, int x, int y):
Thing(SPRITE_SHEET_2, direction) {
	this->velocity  = 750;
	this->clipping  = Main_Resource->clip_bullets[0];
	this->xPosition = x - (clipping.w/2);
	this->yPosition = y - (clipping.h/2);
	this->position  = SDL_Rect{
		(int)xPosition,
		(int)yPosition,
		this->clipping.w,
		this->clipping.h
	};
}

void Bullet::move(uint32_t time) {
	if(atEdgeOfMap()) {
		destroy();
		return;
	}

	Thing::move(time);
}


void Bullet::render() {
	SDL_Rect cam = Main_Window->getCamera();
	if(    xPosition + position.w < cam.x
		|| yPosition + position.h < cam.y
		|| xPosition > cam.x + cam.w
		|| yPosition > cam.y + cam.h
	) return;
	
	// Get position of player RELATIVE to camera
	position.x = xPosition - cam.x;
	position.y = yPosition - cam.y;
	
	SDL_RenderCopyEx(
		Main_Window->getRenderer(),
		texture,
		&clipping,
		&position,
		direction,
		NULL,
		SDL_FLIP_NONE
	);
}

void Bullet::checkHit() {
	
}


bool Bullet::atEdgeOfMap() {
	if(    (xPosition <= 0)
		|| (xPosition + position.w) >= MAP_W
		|| (yPosition <= 0) 
		|| (yPosition + position.h) >= MAP_H 
	) return true;
	return false;
}