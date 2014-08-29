/*
===============================================================================
* File: TileMap.hpp
*
* Author: Andrew Killian
*
* Email: Inceniium@gmail.com
*
* Description: A container of tiles which represents a map/level
===============================================================================
*/

#ifndef TILE_MAP_HPP
#define TILE_MAP_HPP

#include <memory>
#include <string>
#include <vector>

#include "SDL2/SDL.h"

#include "D2DLogger.hpp"
#include "D2DTexture.hpp"

class TileMap {
  public:
    TileMap();
    ~TileMap();

    void loadFromFile(std::string filename);

    void render(SDL_Renderer* renderer);

  private:
    class Tile {
      public:
        Tile(int x, int y, int w, int h, int tileSpriteIndex,
             bool hasCollision=true);

        ~Tile();

        void render(SDL_Renderer* renderer, TileMap* instance);

        SDL_Rect getCollisionRect();
        bool isCollidable();

      private:
        int m_x, m_y, m_w, m_h;

        int m_tileSpriteIndex;
        SDL_Rect m_collisionRect;

        bool m_hasCollision;
    };

  public:
    std::vector<SDL_Rect> getCollidableTileRects();
    SDL_Rect getLevelEnd();

  private:
    void loadTileset(std::string image, int margin, int spacing);

  private:
    std::shared_ptr<D2DTexture> m_tilesetImage;

    std::vector<SDL_Rect> m_tileSprites;
    std::vector<Tile> m_tiles;

    SDL_Rect m_levelEnd;

    D2DLogger logger;
};

#endif