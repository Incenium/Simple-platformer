#include <iostream>
#include "json/json.h"

#include "D2DError.hpp"
#include "D2DResourceManager.hpp"
#include "TileMap.hpp"

TileMap::TileMap()
{
    logger.open();
}

TileMap::~TileMap()
{
}

void TileMap::loadFromFile(std::string filename)
{
    Json::Reader reader;
    Json::Value root;

    std::ifstream file;
    std::string line;
    std::string jsonToParse;

    file.open(filename);
    
    if (!file.is_open())
        D2DFail(logger, "Unable to open tile map file!\n");

    while (getline(file, line))
        jsonToParse += line;

    if (!reader.parse(jsonToParse, root)){
        D2DFail(logger,
                "Unable to parse tile map file! Json reader error messages: %s\n", reader.getFormattedErrorMessages().c_str());
    }

    std::string image = "res/" + root["tilesets"][0]["image"].asString();
    int tileWidth = root["tilewidth"].asInt();
    int tileHeight = root["tileheight"].asInt();
    int margin = root["tilesets"][0]["margin"].asInt();
    int spacing = root["tilesets"][0]["spacing"].asInt();

    // load the tileset
    m_tilesetImage = D2DResourceManager::instance().getTexture(image).lock();

    for (int i = 0; i < m_tilesetImage->getHeight(); i += tileWidth){
        for (int j = 0; j < m_tilesetImage->getWidth(); j += tileHeight){
            //TODO: add margin and spacing
            SDL_Rect sprite = {j, i, tileWidth, tileHeight};
            m_tileSprites.push_back(sprite);
        }
    }

    // load the tile map data
    Json::Value tileMapData = root["layers"][0]["data"];
    int mapWidth = root["width"].asInt();
    int mapHeight = root["height"].asInt();

    int tileX = 0;
    int tileY = 0;

    for (int i = 0; i < tileMapData.size(); i++){
        bool hasCollision = true;
        if (root["tilesets"][0]["tileproperties"][std::to_string(tileMapData[i].asInt() - 1)]["hasCollision"].asString() == "false"){
            
            hasCollision = false;
        }

        Tile t(tileX, tileY, tileWidth, tileHeight,
               tileMapData[i].asInt() - 1, hasCollision);

        m_tiles.push_back(t);

        tileX += tileWidth;
        if (tileX >= mapWidth * tileWidth){
            tileX = 0;
            tileY += tileHeight;
        }
    }

    // VERY GAME SPECIFIC
    m_levelEnd.x = root["layers"][1]["objects"][0]["x"].asInt();
    m_levelEnd.y = root["layers"][1]["objects"][0]["y"].asInt();
    m_levelEnd.w = root["layers"][1]["objects"][0]["width"].asInt();
    m_levelEnd.h = root["layers"][1]["objects"][0]["height"].asInt();
}

void TileMap::render(SDL_Renderer* renderer)
{
    for (int i = 0; i < m_tiles.size(); i++){
        m_tiles[i].render(renderer, this);
    }
}

std::vector<SDL_Rect> TileMap::getCollidableTileRects()
{
    std::vector<SDL_Rect> res;
    for (int i = 0; i < m_tiles.size(); i++){
        if (m_tiles[i].isCollidable())
            res.push_back(m_tiles[i].getCollisionRect());
    }

    return res;
}

SDL_Rect TileMap::getLevelEnd()
{
    return m_levelEnd;
}

TileMap::Tile::Tile(int x, int y, int w, int h, int tileSpriteIndex,
                    bool hasCollision)
{
    m_x = x;
    m_y = y;

    m_collisionRect = {m_x, m_y, w, h};

    m_tileSpriteIndex = tileSpriteIndex;

    m_hasCollision = hasCollision;
}

TileMap::Tile::~Tile()
{
}

void TileMap::Tile::render(SDL_Renderer* renderer, TileMap* instance)
{
    instance->m_tilesetImage->render(m_x, m_y, renderer,
                                     &instance->m_tileSprites[m_tileSpriteIndex]);
}

SDL_Rect TileMap::Tile::getCollisionRect()
{
    return m_collisionRect;
}

bool TileMap::Tile::isCollidable()
{
    return m_hasCollision;
}