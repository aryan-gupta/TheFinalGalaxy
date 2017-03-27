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
 * @date			2017-03-25 (YYYY-MM-DD)
 * @version		1.0.0
 * @description 	
 * =============================================================================
**/
#include "info.h"

#include <SDL.h>
#include <cmath>

#include ".\inc\main.h"
#include ".\inc\Thing.h"
#include ".\inc\Resources.h"
#include ".\inc\Window.h"

#define _USE_MATH_DEFINES

Thing::Thing(SpriteSheets sheet, double direction) {
	this->texture = Main_Resource->spriteSheets[sheet];
	// xPosition will be instantiated in derived class
	// yPosition will be instantiated in derived class
	this->velocity  = 0.0;
	// position will be instantiated in derived class
	// clipping will be instantiated in derived class
	this->direction = direction;
	this->isExploding = false;
	this->explosionCounter = 0;
}


Thing::~Thing() {
	texture = nullptr;
	explosion = nullptr;
}


void Thing::render() {
	if(isExploding) {
		clipping.x = (explosionCounter % 9) * 100;
		clipping.y = (explosionCounter / 9) * 100;
	}
	
	SDL_RenderCopyEx(
		Main_Window->getRenderer(),
		texture,
		&clipping,
		&position,
		direction,
		NULL,
		SDL_FLIP_VERTICAL
	);
}


void Thing::move(uint32_t time) {
	checkHit();
	
	if(explosionCounter >= 80)
		destroy();
	
	if(isExploding) {
		explosionCounter++;
		return;
	}
	
	xPosition -= sin((360 - direction) * M_PI/180) * velocity * (time/1000.0);
	yPosition -= cos((360 - direction) * M_PI/180) * velocity * (time/1000.0);
	
	keepInMap();
	updatePosition();
}


void Thing::explode() {
	isExploding = true;
	explosionCounter = 0;
	
	texture = Main_Resource->explosion;
	clipping = SDL_Rect{
		0, 
		0, 
		clipping.w, 
		clipping.w
	};
}


void Thing::keepInMap() {
	if(xPosition < 0)
		xPosition = 0;
	
	if((xPosition + position.w) > SCRN_W) 
		xPosition = SCRN_W - clipping.w;
	
	if(yPosition < 0) 
		yPosition = 0;
	
	if((yPosition + position.h) > SCRN_H) 
		yPosition = SCRN_H - clipping.h;
}

void Thing::updatePosition() {
	position.x = (int)xPosition;
	position.y = (int)yPosition;
}