/*
===============================================================================
* File: D2DSpritesheet.hpp
*
* Author: Andrew Killian
*
* Email: Inceniium@gmail.com
*
* Description: Collection of sprites in one texture
===============================================================================
*/

#ifndef D2D_SPRITESHEET_HPP
#define D2D_SPRITESHEET_HPP

#include <map>
#include <memory>

#include <string>
#include <vector>

#include "json/json.h"

#include "SDL2/SDL.h"

#include "D2DLogger.hpp"
#include "D2DTexture.hpp"

class D2DSpritesheet {
  public:
    D2DSpritesheet();
    ~D2DSpritesheet();

    // Loads a *.spritesheet file containing info about the spritesheet
    void loadFromFile(std::string path, SDL_Renderer* renderer);

    void render(SDL_Rect* sprite, int x, int y, SDL_Renderer* renderer);

    SDL_Rect* getSprite(std::string spriteName);

  private:
    class Sprite {
      public:
        Sprite();
        ~Sprite();

        void createFromJson(Json::Value jsonSpriteObject,
                            D2DSpritesheet* instance);

        SDL_Rect getRect();

        // Mainly used for SDL rendering where the SDL_Rect must be passed by
        // reference
        SDL_Rect* getRectReference();

      private:
        SDL_Rect m_spriteRect;
    };

  private:
    void loadSpriteMap(Json::Value jsonSpriteArray);

  private:
    // The spritesheet texture
    std::shared_ptr<D2DTexture> m_spritesheet;

    // map of sprites
    std::map<std::string, Sprite> m_sprites;

    D2DLogger logger;
};

#endif