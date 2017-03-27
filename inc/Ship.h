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

#ifndef SHIP_H_INC
#define SHIP_H_INC

#include <stdint.h>

#include ".\Thing.h"
#include ".\Resources.h"
class Bullet;

/// @brief A Ship abstract class
class Ship : public Thing {
public:
	/// @brief Creates a ship
	/// @param [in] sheet `SpriteSheets`  The sprite-sheet to use
	/// @sa SpriteSheets
	/** @warning These following class members must be instantiated in base class
			- \ref xPosition
			- \ref yPosition
			- \ref position
			- \ref clipping
	**/
	Ship(SpriteSheets sheet, double direction);
	virtual ~Ship(); /// Default destructor
	
	virtual void fire() = 0; ///< Fires a bullet
	
	/// @brief Moves based on time
	/// @param [in] time `uint32_t` the amount of time passed from the last move call
	virtual void move(uint32_t time) = 0;
protected:

	/// @brief Pure virtual functions from base class
	/// @warning Must be instantiated in derived class
	/// @sa Thing::destroy() Thing::checkHit()
	virtual void destroy() = 0;
	virtual void checkHit() = 0;
private:
};

#endif