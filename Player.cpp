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

#include <cmath>
#include <SDL.h>
#include <vector>
using std::vector;

#include ".\inc\main.h"
#include ".\inc\Player.h"
#include ".\inc\Window.h"
#include ".\inc\Bullet.h"
#include ".\inc\Asteroid.h"

const double TURN_VELOCITY = 5.0;
const double VELOCITY = 400.0; // 10px per second

Player::Player():
Ship(SPRITE_SHEET_2, 0.0) {
	shieldTexture = Main_Resource->spriteSheets[SPRITE_SHEET_1]; // set the shield Texture
	shieldClipping = Main_Resource->clip_shield;
	
	clipping = Main_Resource->clip_playerShips[PLAYER_SHIP_1];
	
	position = SDL_Rect {
		MAP_W/2 - clipping.w/2,
		MAP_H/2 - clipping.h/2,
		clipping.w,
		clipping.h
	};
	
	shieldPosition = SDL_Rect{0, 0, shieldClipping.w, shieldClipping.h};
	
	shieldCenter = SDL_Point{
		shieldClipping.w/2,
		shieldClipping.h/2 + 10
	};
	
	xPosition = position.x;
	yPosition = position.y;
	
	hasRapidFire  = false;
	RFcounter     = 0;
	hasDoubleFire = false;
	DFcounter     = 0;
	hasShield     = false;
	shieldCounter = 0;
}


void Player::turn(uint32_t time) {
	direction -= turnVelocity;
	
	if(direction > 360)
		direction = 0;
	if(direction < 0)
		direction = 360;
}


void Player::setTurn(Direction direction) {
	switch(direction) {
		case LEFT_DIRECTION:
			turnVelocity = TURN_VELOCITY;
		break;
		
		case RIGHT_DIRECTION:
			turnVelocity = -TURN_VELOCITY;
		break;
		
		default:
			turnVelocity = 0;
		break;
	}
}


void Player::setMoving(Direction direction) {
	switch(direction) {
		case UP_DIRECTION:
			velocity = VELOCITY;
		break;
		
		case DOWN_DIRECTION:
			velocity = -VELOCITY;
		break;
		
		default:
			velocity = 0;
		break;
	}
}


void Player::move(uint32_t time) {
	if(collisionWithAsteroid()) {
		xPosition += sin((360 - direction) * M_PI/180) * velocity * (time/1000.0);
		yPosition += cos((360 - direction) * M_PI/180) * velocity * (time/1000.0);
		return;
	}
	
	Thing::move(time);
	turn(time);
	keepInMap();
	
	if(hasShield) {
		double dirInRads = (360 - direction) * M_PI/180;
		shieldPosition.x -= sin(dirInRads) * velocity * (time/1000.0);
		shieldPosition.y -= cos(dirInRads) * velocity * (time/1000.0);
	
	}
}


void Player::render() {
	Thing::render();
	
	if(hasShield) {
		shieldPosition = SDL_Rect{
			position.x - shieldClipping.w/2 + position.w/2,
			position.y - shieldClipping.h/2 + position.h/2 - 10,
			shieldClipping.w,
			shieldClipping.h
		};
		
		SDL_RenderCopyEx( // Draw the ship on the renderer
			Main_Window->getRenderer(),
			this->shieldTexture,
			&this->shieldClipping,
			&shieldPosition,
			direction,
			&shieldCenter,
			SDL_FLIP_NONE
		);
	}
}


void Player::turnOnRapidFire() {
	this->hasRapidFire = true;
	this->RFcounter = 0;
}


void Player::turnOnDoubleFire() {
	this->hasDoubleFire = true;
	this->DFcounter = 0;
}


void Player::turnOnShield() {
	this->hasShield = true;
	this->shieldCounter = 0;
}


void Player::centerCamOverUs(int& x, int& y) {
	x = xPosition - (SCRN_W/2) + (clipping.w/2);
	y = yPosition - (SCRN_H/2) + (clipping.h/2);
}


Powerup* Player::getPowerup() {
	return nullptr;
}


void Player::checkHit() {	
	for(auto b : Main_Window->getEnemyBullets()) {
		if(checkCollision(b->getPosition(), this->position)) {
			//b->explode();
			this->explode();
		}
	}
}


void Player::fire() {
	Main_Window->addPlayerBullet(new Bullet(
		this->direction, 
		this->xPosition + (clipping.w / 2), 
		this->yPosition + (clipping.h / 2)
	));
}


void Player::keepInMap() {
	if(xPosition < 0)
		xPosition = 0;
	
	if((xPosition + position.w) > MAP_W) 
		xPosition = MAP_W - clipping.w;
	
	if(yPosition < 0) 
		yPosition = 0;
	
	if((yPosition + position.h) > MAP_H) 
		yPosition = MAP_H - clipping.h;
}


bool Player::collisionWithAsteroid() {
	for(auto a : Main_Window->getAsteroids()) {
		if(checkCollision(a->getPosition(), this->position))
			return true;
	}
	
	return false;
}