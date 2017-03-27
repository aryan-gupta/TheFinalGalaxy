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

#ifndef PLAYER_H_INC
#define PLAYER_H_INC

#include ".\Ship.h"
class Powerup;

extern const double VELOCITY; //< Stores the velocity of the Player

enum PlayerShipTypes {
	PLAYER_SHIP_1,
	//PLAYER_SHIP_2,
	//PLAYER_SHIP_3,
	TOTAL_PLAYER_SHIPS
};

class Player : public Ship {
public:
	Player();  ///< Constructor for the player's Ship
	virtual ~Player(); ///< Destructor for player's Ship
	
	/// @brief Set the turn direction
	/// @param [in] direction `Direction` - the direction to turn
	/// @sa Direction
	/// Possible direction for movement is Left, Right, and No movement
	void setTurn(Direction direction);
	
	/// @brief Set the movement direction
	/// @param [in] direction `Direction` - the direction to move
	/// @sa Direction
	/// Possible direction for movement is Up, Down, and No movement
	void setMoving(Direction direction);
	
	void turnOnRapidFire();  ///< Turns on rapid fire
	void turnOnDoubleFire(); ///< Turns on double fire
	void turnOnShield();     ///< Turns on shield
	
	/// @brief Moves based on time
	/// @param [in] time `uint32_t` the amount of time passed from the last move call
	virtual void move(uint32_t time);
	
	
	virtual void fire();   ///< Fires a bullet
	virtual void render(); ///< Renders the player
protected:
	SDL_Texture* shieldTexture;
	SDL_Rect shieldClipping;
	SDL_Rect shieldPosition;
	bool hasShield;
	int shieldCounter;
	
	bool hasRapidFire;
	int RFcounter;
	
	bool hasDoubleFire;
	int DFcounter;
	
	double turnVelocity;
	
	Powerup* getPowerup();
	void turn(uint32_t time);
	
	virtual void destroy();
	virtual void checkHit();
private:
};

#endif