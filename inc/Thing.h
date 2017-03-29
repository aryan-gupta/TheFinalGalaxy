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

#ifndef THING_H_INC
#define THING_H_INC

#include <SDL.h>

#include ".\main.h"

/// @brief A object on the screen
/// A abstract base class used to derive classes that can be rendered on the screen. 
class Thing {
public:
	/// @brief Base class Constructor
	/// @param [in] sheet `SpriteSheets`  The sprite-sheet to use
	/// @param [in] direction `double`    The direction to instantiate the Thing at
	/// @sa SpriteSheets
	/** @warning These following class members must be instantiated in base class
			- \ref xPosition
			- \ref yPosition
			- \ref position
			- \ref clipping
	**/
	Thing(SpriteSheets sheet, double direction);
	virtual ~Thing(); /// Base class Destructor

	void explode(); ///< Explodes the current thing>
	
	/// @brief Destroys this thing
	/// @warning pure virtual function - Must be defined in Base Class
	/// Removes itself from the vectors storing the Thing then deletes it self
	void destroy();
	
	/// @brief get the current position of the Thing
	/// @return `SDL_Rect` Returns the SDL_Rect position of the current Thing
	/// @note `inline` function
	inline SDL_Rect& getPosition();
	
	/// @brief Render the Thing
	/// @note virtual function
	virtual void render();
	
	/// @brief Moves the Thing based on time
	/// @param [in] time `uint32_t` the amount of time passed from the last move call
	/// @note virtual function
	virtual void move(uint32_t time);
protected:
	SDL_Texture* texture; ///< Pointer to the texture in \ref Resources for this Thing
	double xPosition;     ///< Internal x position of the Thing
    double yPosition;     ///< Internal y position of the Thing
	
	SDL_Rect position; ///< SDL_Rect position of the Thing RELITIVE to the camera
	
	/// @brief SDL_Rect clipping of the Thing
	/// @note Copied from \ref Resources struct
	SDL_Rect clipping;
	
	double velocity;  ///< Velocity of the Thing
	
	/// @brief Direction of the Thing in degrees
	/// @note 0 degrees is North and 90 degrees is East
	double direction;
	
	SDL_Texture* explosion; ///< Pointer to the texture in \ref Resources for the explosion
	bool isExploding;       ///< Is the Thing exploding
	int explosionCounter;   ///< Counts/times the explosion to decide which clipping to use
	
	/// @brief checks if something has hit it
	/// @warning pure virtual function - Must be defined in Base Class
	virtual void checkHit() = 0;
private:
	void keepInMap(); ///< Keeps the Thing inside the map
};

inline
SDL_Rect& Thing::getPosition() {
	return position;
}

#endif