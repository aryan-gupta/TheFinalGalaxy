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

/// @brief A enemy on the screen
class Enemy : public Ship {
public:
	Enemy(); ///< Default constructor
	virtual ~Enemy() {}; ///< Default Destructor

	virtual void fire(); ///< Fires a bullet

	/// @brief Moves the Thing based on time
	/// @param [in] time `uint32_t` the amount of time passed from the last move call
	/// @note virtual function
	virtual void move(uint32_t time);
protected:
	virtual void checkHit(); ///< checks for a hit by a \ref Player \ref Ship's \ref Bullet
private:
	void turn(int degrees); ///< Turns the enemy by a certain degrees
	
	/// @brief checks whether we are at the map or not1
	/// @return `bool` Whether the Enemy is at the edge of the map or not1
	/// @retval TRUE The Enemy is at the edge of the map
	/// @retval FALSE The Enemy is at not the edge of the map
	bool atEdgeOfMap();
};

#endif