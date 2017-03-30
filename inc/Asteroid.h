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

/// @brief an Asteroid
class Asteroid : public Thing {
public: 
	Asteroid(); ///< @brief Default constructor
	virtual ~Asteroid() {} ///< Default destructor
	
	///< Sets the movement of the the asteroid
	void moveAsteroid(double direction, double velocity);
	
	/// @brief Moves the Thing based on time
	/// @param [in] time `uint32_t` the amount of time passed from the last move call
	/// @note virtual function
	virtual void move(uint32_t time);
	
	/// @brief Render the Thing
	/// @note virtual function
	virtual void render();
protected:
	void keepInMap(); ///< Keeps the Asteroid in the map
	
	/// @brief checks if something has hit it
	/// @warning pure virtual function - Must be defined in Base Class
	virtual void checkHit();
private:
};


#endif