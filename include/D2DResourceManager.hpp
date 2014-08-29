/*
===============================================================================
* File: ResourceManager.hpp
*
* Author: Andrew Killian
*
* Email: Inceniium@gmail.com
*
* Description: (Singelton) Manages the resources for the game
===============================================================================
*/

#ifndef D2D_RESOURCE_MANAGER_HPP
#define D2D_RESOURCE_MANAGER_HPP

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "D2DAnimation.hpp"
#include "D2DError.hpp"
#include "D2DLogger.hpp"
#include "D2DMusic.hpp"
#include "D2DSoundEffect.hpp"
#include "D2DSpritesheet.hpp"

#include "json/json.h"

class D2DAnimation;

class D2DResourceManager {
  public:
    static D2DResourceManager& instance();
    ~D2DResourceManager();

    bool loadResources(std::string path, SDL_Renderer* renderer);

    std::weak_ptr<D2DTexture>     getTexture(std::string texture);
    std::weak_ptr<D2DSpritesheet> getSpritesheet(std::string spritesheet);
    std::weak_ptr<D2DAnimation>   getAnimation(std::string animation);
    std::weak_ptr<D2DMusic>       getMusic(std::string music);
    std::weak_ptr<D2DSoundEffect> getSoundEffect(std::string soundEffect);

  private:
    D2DResourceManager();

    // loadResources() helper functions
    void loadTextures(Json::Value textures, SDL_Renderer* renderer);
    void loadSpritesheets(Json::Value spritesheets, SDL_Renderer* renderer);
    void loadAnimations(Json::Value animations);
    void loadMusic(Json::Value musics);
    void loadSoundEffects(Json::Value soundeffects);

  private:
    std::map<std::string, std::shared_ptr<D2DTexture>>     m_textures;
    std::map<std::string, std::shared_ptr<D2DSpritesheet>> m_spritesheets;
    std::map<std::string, std::shared_ptr<D2DAnimation>>   m_animations;
    std::map<std::string, std::shared_ptr<D2DMusic>>       m_music;
    std::map<std::string, std::shared_ptr<D2DSoundEffect>> m_soundeffects;

    D2DLogger logger;
};

#endif