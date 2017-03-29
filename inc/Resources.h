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
 * @date			(YYYY-MM-DD)
 * @version		1.0.0
 * @brief 	
 * =============================================================================
**/

#ifndef RESOURCE_H_INC
#define RESOURCE_H_INC

#include <SDL.h>
#include <SDL_Image.h>

extern const char* SPRITE_RES[];     ///< Stores all the locations of the sprite-sheets
extern const char* EXPLOSION_RES;    ///< Stores the explosion animation sprite-sheet
extern const char* BACKGROUND_IMAGE; ///< Background image location
extern const char* MAIN_FONT;        ///< Main font location
extern const char* LIFE_IMAGE;       ///< Stores the image used for number of lives

/// @brief Stores all of our resources
/**
	This Struct was implemented so the program doesn't have to
		- load the image, then ...
		- convert to surface, then ...
		- convert to renderer
	
	every time a object is created. Which was causing major lags. \n
	After this struct is created, this struct contains all of the textures we
	will need. So there is only one bullet texture, one ship texture. However,
	whenever we create the class, it uses the texture as a <em>Shared Resource</em>. 
	That is why we never destroy our textures in our class destructors. Doing so
	would delete the image and we cant access the texture when creating another
	object.
**/
struct Resources {
	Resources();  ///< @brief Loads all the images and resources
	~Resources(); ///< @brief Frees all of the textures and surfaces used in the game
	
	SDL_Texture** spriteSheets; ///< Array of all the textures for the sprite-sheets
	SDL_Texture*  explosion;    ///< Texture for the explosion sprite-sheet
	
	SDL_Texture*  background;  ///< Stores our background texture
	SDL_Texture*  healthHeart; ///< Stores out texture for our heart
	//TTF_Font*     mainFont;    ///< Stores the main font we will be using
	//TTF_Font*     briefFont;   ///< Stores the brief/paragraph font
	//TTF_Font*     titleFont;   ///< Stores the title font
	
	// SPRITE SHEET 0
	SDL_Rect* clip_enemyShips; ///< Array for all the enemy ship clippings
	SDL_Rect* clip_astroids;   ///< Array for all the asteroid sprite clippings
	SDL_Rect* clip_powerup;    ///< Array for all the power-up sprite clippings
	SDL_Rect  clip_shield;     ///< The shield clippings
	
	// SPRITE SHEET 1
	SDL_Rect* clip_playerShips; ///< Array for the player \ref Ship's clipping
	SDL_Rect* clip_bullets;     ///< Array for the different bullet's clipping
	
	//Mix_Music* music;
	//Mix_Chunk* fire;
private:
	/// @brief Loads a image file in to a texture
	/// @param [in] the location of the file to load
	/// @return @a `SDL_Texture*` the loaded texture
	SDL_Texture* load(const char* file);
};

#endif