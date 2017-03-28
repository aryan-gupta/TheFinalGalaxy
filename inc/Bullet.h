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
 * @date			2017-03-27 (YYYY-MM-DD)
 * @version		1.0.0
 * @description 	
 * =============================================================================
**/

#ifndef BULLET_H_INC
#define BULLET_H_INC

#include ".\Thing.h"

class Bullet : public Thing {
public:
	Bullet(double direction, int x, int y, Shooters ship);
	virtual ~Bullet();
	
	virtual void move(uint32_t time);
	virtual void render();
protected:
	virtual void destroy();
	virtual void checkHit();
private:
	Shooters whosBullet;
};

#endif