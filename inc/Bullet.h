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

/// @brief A Bullet/Missile on the map
class Bullet : public Thing {
public:
	/// @brief Constructor
	/// @param [in] direction `double` The angle at which to launch the bullet
	/// @param [in] x `int` The x coordinate of the bullet
	/// @param [in] y `int` The y coordinate of the bullet
	Bullet(double direction, int x, int y);
	virtual ~Bullet() {} ///< Destructor Definition
	
	virtual void move(uint32_t time); ///< Moves the bullet and does checks
	virtual void render(); ///< Renders the bullet
protected:
	/// @brief checks whether we are at the map or not1
	/// @return `bool` Whether the bullet is at the edge of the map or not1
	/// @retval TRUE The bullet is at the edge of the map
	/// @retval FALSE The bullet is at not the edge of the map
	bool atEdgeOfMap();
	
	virtual void checkHit(); ///< Checks if this bullet was hit by another bullet
private:
};

#endif