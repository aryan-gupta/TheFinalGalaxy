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
	clipping = Main_Resource->clip_astroids[rand() % 20]; // randomizes the asteroid
	position = SDL_Rect {
		rand() % (MAP_W - clipping.w),  // randomize the position of the asteroid
		rand() % (MAP_H - clipping.h),
		clipping.w,
		clipping.h
	};
	xPosition = position.x;
	yPosition = position.y;
}


void Asteroid::move(uint32_t time) {
	velocity -= 5; // Slow down the Asteroid by 5 each frame
	if(velocity < 0.1) // Make sure the velocity isn't negative
		velocity = 0.1;
	
	Thing::move(time); // Move the Asteroid if velocity is 
	keepInMap(); // Keep the Asteroid in the map
}


void Asteroid::render() { // Not using Thing::move() because we need to keep initial rotation
	if(isExploding) {
		clipping.x = (explosionCounter % 9) * 100;
		clipping.y = (explosionCounter / 9) * 100;
	}
	
	// Get position of player RELATIVE to camera
	position.x = xPosition - Main_Window->getCamera().x;
	position.y = yPosition - Main_Window->getCamera().y;
	
	SDL_RenderCopy(
		Main_Window->getRenderer(),
		texture,
		&clipping,
		&position
	);
}


void Asteroid::checkHit() {
	// Check hits with Player bullets
	for(auto b : Main_Window->getPlayerBullets()) {
		if(checkCollision(b->getPosition(), this->position)) {
			//b->explode();
			this->explode();
		}
	}
	
	// Check hits with Enemy bullets
	for(auto b : Main_Window->getEnemyBullets()) {
		if(checkCollision(b->getPosition(), this->position)) {
			//b->explode();
			this->explode();
		}
	}
}


void Asteroid::moveAsteroid(double direction, double velocity) {
	this->direction = direction;
	this->velocity = velocity + 2.5; // Increase the velocity
}


void Asteroid::keepInMap() {
	if(xPosition < 0)
		xPosition = 0;
	
	if((xPosition + position.w) > MAP_W) 
		xPosition = MAP_W - clipping.w;
	
	if(yPosition < 0) 
		yPosition = 0;
	
	if((yPosition + position.h) > MAP_H) 
		yPosition = MAP_H - clipping.h;
}