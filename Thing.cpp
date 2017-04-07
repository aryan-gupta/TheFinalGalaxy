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
	this->velocity  = 0.1;
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
		SDL_FLIP_VERTICAL
	);
}


void Thing::move(uint32_t time) {
	if(this->explosionCounter >= 80) {
		destroy();
		return;
	}
	
	if(isExploding) {
		explosionCounter++;
		return;
	}
	
	xPosition -= sin((360 - direction) * M_PI/180) * velocity * (time/1000.0);
	yPosition -= cos((360 - direction) * M_PI/180) * velocity * (time/1000.0);
	
	checkHit();
}


void Thing::explode() {
	if(isExploding) // if already exploding, don't do anything
		return;
	
	isExploding = true;
	explosionCounter = 0;
	
	texture = Main_Resource->explosion;
	clipping = SDL_Rect{
		0, 
		0, 
		100, 
		100
	};
}


void Thing::destroy() {
	Main_Window->addThingsToRemove(this);
}