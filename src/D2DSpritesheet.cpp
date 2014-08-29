#include "D2DError.hpp"
#include "D2DResourceManager.hpp"
#include "D2DSpritesheet.hpp"

D2DSpritesheet::D2DSpritesheet()
{
    m_spritesheet = nullptr;

    logger.open();
}

D2DSpritesheet::~D2DSpritesheet()
{
    m_spritesheet->free();
    m_spritesheet = nullptr;

    m_sprites.clear();
}

// TODO: requires some restructure still, come back to this function after
// refactoring the other ones
void D2DSpritesheet::loadFromFile(std::string path, SDL_Renderer* renderer)
{
    Json::Reader reader;
    Json::Value root;

    std::ifstream file;
    std::string line;
    std::string jsonToParse;

    file.open(path);

    if (!file.is_open()){
        D2DWriteErrorContexts(logger);

        logger.write("Unable to open spritesheet file!\n");
        
        exit(EXIT_FAILURE);
    }

    while (getline(file, line))
        jsonToParse += line;

    if (!reader.parse(jsonToParse, root)){
        D2DWriteErrorContexts(logger);

        logger.write("Unable to parse spritesheet file! Json reader error messages: %s\n", reader.getFormattedErrorMessages().c_str());

        exit(EXIT_FAILURE);    
    }

    if (root["texture"] == Json::Value::null){
        D2DWriteErrorContexts(logger);

        logger.write("Member \"texture\" is missing from spritesheet file\n");

        exit(EXIT_FAILURE);
    }

    if (root["sprites"] == Json::Value::null){
        D2DWriteErrorContexts(logger);

        logger.write("Member \"sprites\" is missing from spritesheet file!\n");

        exit(EXIT_FAILURE);
    }

    m_spritesheet = D2DResourceManager::instance().getTexture(root["texture"].asString()).lock();

    if (m_spritesheet == nullptr){
        D2DWriteErrorContexts(logger);

        logger.write("texture %s does not exist!\n",
                     root["texture"].asCString());

        exit(EXIT_FAILURE);
    }

    D2DErrorContext ec("when loading sprites from array: ", "sprites");
    loadSpriteMap(root["sprites"]);
}

void D2DSpritesheet::render(SDL_Rect* sprite, int x, int y,
                         SDL_Renderer* renderer)
{
    m_spritesheet->render(x, y, renderer, sprite);
}

SDL_Rect* D2DSpritesheet::getSprite(std::string spriteName)
{
    std::map<std::string, D2DSpritesheet::Sprite>::iterator it = m_sprites.find(spriteName);

    if (it == m_sprites.end())
        return nullptr;

    else
        return it->second.getRectReference();
}

// RESTRUCTURE
void D2DSpritesheet::loadSpriteMap(Json::Value jsonSpriteArray)
{
    if (!jsonSpriteArray.isArray()){
        D2DWriteErrorContexts(logger);

        logger.write("Json value passed in must be an array!\n");

        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < jsonSpriteArray.size(); i++){
        if (!jsonSpriteArray[i].isObject()){
            D2DWriteErrorContexts(logger);

            logger.write("Json value at position %d in array \"sprites\" must be an object!\n", i);

            exit(EXIT_FAILURE);
        }

        if (jsonSpriteArray[i]["name"] == Json::Value::null){
            D2DWriteErrorContexts(logger);

            logger.write("Member \"name\" missing in sprite object at position %d in array \"sprites\"!\n", i);

            exit(EXIT_FAILURE);
        }

        D2DErrorContext ec("when creating sprite: ",
                           jsonSpriteArray[i]["name"].asCString());
        
        D2DSpritesheet::Sprite sprite;
        sprite.createFromJson(jsonSpriteArray[i], this);

        m_sprites[jsonSpriteArray[i]["name"].asString()] = sprite;
    }
}

//============================= Inner class Sprite ============================
D2DSpritesheet::Sprite::Sprite()
{
}

D2DSpritesheet::Sprite::~Sprite()
{
}

// RESTRUCTURE
void D2DSpritesheet::Sprite::createFromJson(Json::Value jsonSpriteObject, D2DSpritesheet* instance)
{
    if (!jsonSpriteObject.isObject()){
        D2DWriteErrorContexts(instance->logger);

        instance->logger.write("Json value must be an object!\n");

        exit(EXIT_FAILURE);
    }

    if (jsonSpriteObject["x"] == Json::Value::null ||
        jsonSpriteObject["y"] == Json::Value::null ||
        jsonSpriteObject["w"] == Json::Value::null ||
        jsonSpriteObject["h"] == Json::Value::null){

        D2DWriteErrorContexts(instance->logger);

        instance->logger.write("Member(s) \"x\", \"y\", \"w\", \"h\" missing from sprite object!\n");

        exit(EXIT_FAILURE);
    }

    m_spriteRect = {jsonSpriteObject["x"].asInt(),
                    jsonSpriteObject["y"].asInt(),
                    jsonSpriteObject["w"].asInt(),
                    jsonSpriteObject["h"].asInt()};
}

SDL_Rect D2DSpritesheet::Sprite::getRect()
{
    return m_spriteRect;
}

SDL_Rect* D2DSpritesheet::Sprite::getRectReference()
{
    return &m_spriteRect;
}