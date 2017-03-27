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
#include ".\inc\Bullet.h"
#include ".\inc\Resources.h"
#include ".\inc\Window.h"

Bullet::Bullet(double direction, int x, int y, Shooters ship):
Thing(SPRITE_SHEET_2, direction) {
	this->velocity  = 750;
	this->clipping  = Main_Resource->clip_bullets[0];
	this->position  = SDL_Rect{
		x - (clipping.w/2),
		y - (clipping.h/2),
		this->clipping.w,
		this->clipping.h
	};
	this->xPosition = this->position.x;
	this->yPosition = this->position.y;
	
	this->whosBullet = ship;
}


Bullet::~Bullet() {}


void Bullet::render() {
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


void Bullet::destroy() {
	vector<Bullet*>& enemyBullets = Main_Window->getEnemyBullets();
	for(unsigned i = 0; i < enemyBullets.size(); ++i) {
		if(this == enemyBullets[i])
			enemyBullets.erase(enemyBullets.begin() + i);
	}
	
	// for(unsigned i = 0; i < Main_Window->enemyBullets.size(); ++i) {
		// if(this == Main_Window->enemyBullets[i])
			// Main_Window->enemyBullets.erase(Main_Window->enemyBullets.begin() + i);
	// }
	
	delete this;
}


void Bullet::checkHit() {
	
}