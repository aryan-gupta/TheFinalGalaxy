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

#ifndef ENEMY_H_INC
#define ENEMY_H_INC

#include ".\Ship.h"

class Enemy : public Ship {
public:
	Enemy();
	virtual ~Enemy();
	
	void turn(int degrees);
	
	virtual void move(uint32_t time);
	virtual void fire();
protected:
	virtual void destroy();
	virtual void checkHit();
private:
};

#endif