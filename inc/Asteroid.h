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
 * @date			2017-03-26 (YYYY-MM-DD)
 * @version		    1.0.0
 * @description 	
 * =============================================================================
**/

#ifndef ASTROID_H_INC
#define ASTROID_H_INC

#include ".\Thing.h"

class Asteroid : public Thing {
public: 
	Asteroid();
	virtual ~Asteroid() {}
	
	SDL_Rect& getPosition();
	void moveAsteroid(double direction, double velocity);
	
	virtual void move(uint32_t time);
	virtual void render();
protected:
	/// @brief checks if something has hit it
	/// @warning pure virtual function - Must be defined in Base Class
	virtual void checkHit();
	
	void keepInMap();
private:
};


#endif