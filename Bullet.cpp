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
		0,
		0,
		this->clipping.w,
		this->clipping.h
	};
	this->xPosition = x - (clipping.w/2);
	this->yPosition = y - (clipping.h/2);
	
	this->whosBullet = ship;
}


Bullet::~Bullet() {}


void Bullet::move(uint32_t time) {
	if(atEdgeOfMap())
		destroy();
	Thing::move(time);
}


void Bullet::render() {
	// Get position of player RELATIVE to camera
	position.x = xPosition - Main_Window->getCamera().x;
	position.y = yPosition - Main_Window->getCamera().y;
	
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
	auto bullets = Main_Window->getEnemyBullets();
	for(unsigned i = 0; i < bullets.size(); ++i) {
		if(this == bullets[i])
			bullets.erase(bullets.begin() + i);
	}
	
	bullets = Main_Window->getPlayerBullets();
	for(unsigned i = 0; i < bullets.size(); ++i) {
		if(this == bullets[i])
			bullets.erase(bullets.begin() + i);
	}
	
	delete this;
}


void Bullet::checkHit() {
	
}