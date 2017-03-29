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
 * @date			2017-03-27 (YYYY-MM-DD)
 * @version		1.0.0
 * @description 	
 * =============================================================================
 */
#include "info.h"

#include <SDL.h>
#include <vector>
using std::vector;

#include ".\inc\main.h"
#include ".\inc\Enemy.h"
#include ".\inc\Window.h"
#include ".\inc\Bullet.h"

const int TURN_SEED = 50;
const int FIRE_SEED = 500;

Enemy::Enemy():
Ship(SPRITE_SHEET_1, (rand() % 360)) {
	velocity = 250;
	
	clipping = Main_Resource->clip_enemyShips[0];
	
	position = SDL_Rect {
		rand() % (MAP_W - clipping.w),
		rand() % (MAP_H - clipping.h),
		clipping.w,
		clipping.h
	};
	
	xPosition = position.x;
	yPosition = position.y;
}

Enemy::~Enemy() {}

void Enemy::move(uint32_t time) {
	if(atEdgeOfMap())
		turn(180);
	if(rand() % FIRE_SEED == 0)
		fire();
	if(rand() % TURN_SEED == 0)
		turn((rand() % 20) - 10);
	Thing::move(time);
}


void Enemy::turn(int degrees) {
	direction =+ degrees;
}


void Enemy::fire() {
	Main_Window->addEnemyBullet(new Bullet(
		this->direction, 
		this->xPosition + (clipping.w / 2), 
		this->yPosition + (clipping.h / 2)
	));
}


void Enemy::checkHit() {
	vector<Bullet*>& bullets = Main_Window->getPlayerBullets();
	
	for(auto b : bullets) {
		if(checkCollision(b->getPosition(), this->position)) {
			//b->explode();
			this->explode();
		}
	}
}

bool Enemy::atEdgeOfMap() {
	if(    (xPosition <= 0)
		|| (xPosition + position.w) >= MAP_W
		|| (yPosition <= 0) 
		|| (yPosition + position.h) >= MAP_H 
	) return true;
	return false;
}