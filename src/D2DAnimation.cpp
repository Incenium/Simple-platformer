#include "SDL2/SDL.h"

#include "D2DError.hpp"
#include "D2DResourceManager.hpp"
#include "D2DAnimation.hpp"

D2DAnimation::D2DAnimation()
{
    m_spritesheet = nullptr;

    m_currentFrame = 0;

    m_updateTime = 0;
    m_timeSinceLast = 0;

    logger.open();
}

D2DAnimation::~D2DAnimation()
{
}

void D2DAnimation::loadFromFile(std::string path)
{
    bool success = true;

    Json::Reader reader;
    Json::Value root;

    std::ifstream file;
    std::string line;
    std::string jsonToParse;

    file.open(path);

    if (!file.is_open())
        D2DFail(logger, "Unable to open animation file\n");

    while (getline(file, line))
        jsonToParse += line;

    if (!reader.parse(jsonToParse, root)){
        D2DFail(logger,
                "Unable to parse json in animation file. Json reader error messages: %s\n",
                reader.getFormattedErrorMessages().c_str());
    }

    if (root["spritesheet"] == Json::Value::null){
        D2DFail(logger,
                "Member \"spritesheet\" is missing from animation file\n");
    }

    if (root["frames"] == Json::Value::null){
        D2DFail(logger,
                "Member \"frames\" is missing from spritesheet file\n");
    }

    if (root["update_time"] == Json::Value::null)
        D2DFail(logger, "Member \"update_time\" is missing from animation file\n");

    if (root["update_time"].asInt() == 0)
        D2DFail(logger, "Member \"update_time\" can not be 0!\n");

    {
        D2DErrorContext ec("When getting spritesheet: ",
                       root["spritesheet"].asCString());
        
        getSpritesheet(root["spritesheet"]);
    }

    {
        D2DErrorContext ec("when loading frames from spritesheet: ",
                           root["spritesheet"].asCString());

        loadFrames(root["frames"]);
    }

    m_updateTime = root["update_time"].asInt();
}

void D2DAnimation::run()
{
    if (!m_timer.isStarted()){
        m_timer.start();

        m_currentFrame++;

        m_timeSinceLast = m_timer.getTicks();
    }

    else {
        Uint32 timePassed = m_timer.getTicks() - m_timeSinceLast;

        if (timePassed >= (Uint32)m_updateTime){
            m_currentFrame++;

            if (m_currentFrame > m_frames.size() - 1)
                m_currentFrame = 1;

            m_timeSinceLast = m_timer.getTicks();
        }

        else
            return;
    }
}

void D2DAnimation::render(int x, int y, SDL_Renderer* renderer)
{
    m_spritesheet->render(m_frames[m_currentFrame], x, y, renderer);
}

void D2DAnimation::reset()
{
    m_currentFrame = 0;
}

SDL_Rect* D2DAnimation::getCurrentFrame()
{
    return m_frames[m_currentFrame];
}

void D2DAnimation::getSpritesheet(Json::Value spritesheet)
{
    m_spritesheet = D2DResourceManager::instance().getSpritesheet(spritesheet.asString()).lock();

    if (m_spritesheet == nullptr){
        D2DFail(logger,
                "Unable to get spritesheet %s from the resource manager",
                spritesheet.asCString());
    }
}

void D2DAnimation::loadFrames(Json::Value framesArray)
{
    if (!framesArray.isArray())
        D2DFail(logger, "Json value must be an array!\n");

    for (int i = 0; i < framesArray.size(); i++){
        if (!framesArray[i].isString()){
            D2DFail(logger,
                    "Value at position %d in array \"frames\" must be a string!\n", i);
        }

        if (m_spritesheet->getSprite(framesArray[i].asString()) == nullptr){
            D2DFail(logger, "Unable to get sprite %s from spritesheet!\n",
                    framesArray[i].asCString());
        }

        m_frames.push_back(m_spritesheet->getSprite(framesArray[i].asString()));
    }
}