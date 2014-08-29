#include "D2DResourceManager.hpp"

D2DResourceManager& D2DResourceManager::instance()
{
    static D2DResourceManager* instance = new D2DResourceManager();

    return *instance;
}

D2DResourceManager::~D2DResourceManager()
{
}

bool D2DResourceManager::loadResources(std::string path,
                                       SDL_Renderer* renderer)
{
    Json::Reader reader;
    Json::Value root;

    std::ifstream file;
    std::string line;
    std::string jsonToParse;

    file.open(path);

    if (!file.is_open()){
        logger.write("\tUnable to open resource file %s for reading, file does not exist or is corrupt\n", path.c_str());

        exit(EXIT_FAILURE);
    }

    while (getline(file, line))
        jsonToParse += line;
        
    if (!reader.parse(jsonToParse, root)){
        D2DWriteErrorContexts(logger);
        
        logger.write("\tUnable to parse resource file %s. Json reader error messages: %s\n", path.c_str(),
                     reader.getFormattedErrorMessages().c_str());

        exit(EXIT_FAILURE);
    }

    if (root["textures"] == Json::Value::null){
        D2DWriteErrorContexts(logger);
        
        logger.write("\tMember \"textures\" missing from resource file %s\n",
                     path.c_str());

        exit(EXIT_FAILURE);
    }

    if (root["spritesheets"] == Json::Value::null){
        D2DWriteErrorContexts(logger);
        
        logger.write("\tMember \"spritesheets\" missing from resource file %s\n",
                     path.c_str());

        exit(EXIT_FAILURE);
    }

    if (root["animations"] == Json::Value::null){
        D2DWriteErrorContexts(logger);

        logger.write("\tMember \"animations\" missing from resource file %s\n",
                     path.c_str());

        exit(EXIT_FAILURE);
    }

    if (root["music"] == Json::Value::null){
        D2DWriteErrorContexts(logger);

        logger.write("\tMember \"music\" missing from resource file %s\n",
                     path.c_str());

        exit(EXIT_FAILURE);
    }

    if (root["soundeffects"] == Json::Value::null){
        D2DWriteErrorContexts(logger);

        logger.write("\tMember \"soundeffects\" missing from resource file %s\n",
                     path.c_str());

        exit(EXIT_FAILURE);
    }

    loadTextures(root["textures"], renderer);
    loadSpritesheets(root["spritesheets"], renderer);
    loadAnimations(root["animations"]);
    loadMusic(root["music"]);
    loadSoundEffects(root["soundeffects"]);
}

std::weak_ptr<D2DTexture> D2DResourceManager::getTexture(std::string texture)
{
    std::map<std::string, std::shared_ptr<D2DTexture>>::iterator it = m_textures.find(texture);

    if (it == m_textures.end()){
        std::weak_ptr<D2DTexture> null;

        return null;
    }

    else {
        std::weak_ptr<D2DTexture> texture(it->second);

        return texture;
    }
}

std::weak_ptr<D2DSpritesheet> D2DResourceManager::getSpritesheet(std::string spritesheet)
{
    std::map<std::string, std::shared_ptr<D2DSpritesheet>>::iterator it = m_spritesheets.find(spritesheet);

    if (it == m_spritesheets.end()){
        std::weak_ptr<D2DSpritesheet> null;

        return null;
    }

    else {
        std::weak_ptr<D2DSpritesheet> spritesheet(it->second);

        return spritesheet;
    }
}

std::weak_ptr<D2DAnimation> D2DResourceManager::getAnimation(std::string animation)
{
    std::map<std::string, std::shared_ptr<D2DAnimation>>::iterator it = m_animations.find(animation);

    if (it == m_animations.end()){
        std::weak_ptr<D2DAnimation> null;

        return null;
    }

    else {
        std::weak_ptr<D2DAnimation> animation(it->second);

        return animation;
    }
}

std::weak_ptr<D2DMusic> D2DResourceManager::getMusic(std::string music)
{
    std::map<std::string, std::shared_ptr<D2DMusic>>::iterator it = m_music.find(music);

    if (it == m_music.end()){
        std::weak_ptr<D2DMusic> null;

        return null;
    }

    else {
        std::weak_ptr<D2DMusic> music(it->second);

        return music;
    }
}

std::weak_ptr<D2DSoundEffect> D2DResourceManager::getSoundEffect(std::string soundEffect)
{
    std::map<std::string, std::shared_ptr<D2DSoundEffect>>::iterator it = m_soundeffects.find(soundEffect);

    if (it == m_soundeffects.end()){
        std::weak_ptr<D2DSoundEffect> null;

        return null;
    }

    else {
        std::weak_ptr<D2DSoundEffect> soundEffect(it->second);

        return soundEffect;
    }
}

D2DResourceManager::D2DResourceManager()
{
    logger.open();
}

void D2DResourceManager::loadTextures(Json::Value textures,
                                      SDL_Renderer* renderer)
{
    if (!textures.isArray()){
        D2DWriteErrorContexts(logger);

        logger.write("Member \"textures\" must be an array!\n");

        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < textures.size(); i++){
        if (!textures[i].isString()){
            D2DWriteErrorContexts(logger);

            logger.write("Value at position %d in array \"textures\" must be a string!\n", i);
            
            exit(EXIT_FAILURE);
        }

        std::shared_ptr<D2DTexture> texture(new D2DTexture());

        D2DErrorContext ec("when loading texture: ", textures[i].asCString());
        texture->loadFromFile(textures[i].asString(), renderer);

        m_textures[textures[i].asString()] = texture;
    }
}

void D2DResourceManager::loadSpritesheets(Json::Value spritesheets,
                                          SDL_Renderer* renderer)
{
    if (!spritesheets.isArray()){
        D2DWriteErrorContexts(logger);

        logger.write("Member \"spritesheets\" must be an array!\n");

        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < spritesheets.size(); i++){
        if (!spritesheets[i].isString()){
            D2DWriteErrorContexts(logger);

            logger.write("Value at position %d in array \"spritesheets\" must be a string!\n", i);

            exit(EXIT_FAILURE);
        }

        std::shared_ptr<D2DSpritesheet> spritesheet(new D2DSpritesheet());

        D2DErrorContext ec("when loading spritesheet: ",
                           spritesheets[i].asCString());

        spritesheet->loadFromFile(spritesheets[i].asString(), renderer);

        m_spritesheets[spritesheets[i].asString()] = spritesheet;
    }
}

void D2DResourceManager::loadAnimations(Json::Value animations)
{
    if (!animations.isArray()){
        D2DWriteErrorContexts(logger);

        logger.write("Member \"animations\" must be an array!\n");

        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < animations.size(); i++){
        if (!animations[i].isString()){
            D2DWriteErrorContexts(logger);

            logger.write("Value at position %d in array \"animations\" must be a string!\n", i);
            
            exit(EXIT_FAILURE);
        }

        std::shared_ptr<D2DAnimation> animation(new D2DAnimation());

        D2DErrorContext ec("when loading animation: ",
                           animations[i].asCString());

        animation->loadFromFile(animations[i].asString());

        m_animations[animations[i].asString()] = animation;
    }
}

void D2DResourceManager::loadMusic(Json::Value musics)
{
    if (!musics.isArray()){
        D2DWriteErrorContexts(logger);

        logger.write("Member \"music\" must be an array!\n");

        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < musics.size(); i++){
        if (!musics[i].isString()){
            D2DWriteErrorContexts(logger);

            logger.write("Value at position %d in array \"music\" must be a string!\n", i);

            exit(EXIT_FAILURE);
        }

        std::shared_ptr<D2DMusic> music(new D2DMusic());

        D2DErrorContext ec("when loading music: ", musics[i].asCString());
        music->loadFromFile(musics[i].asString());

        m_music[musics[i].asString()] = music;
    }
}

void D2DResourceManager::loadSoundEffects(Json::Value soundeffects)
{
    if (!soundeffects.isArray()){
        D2DWriteErrorContexts(logger);

        logger.write("Member \"soundeffects\" must be an array!\n");

        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < soundeffects.size(); i++){
        if (!soundeffects[i].isString()){
            D2DWriteErrorContexts(logger);

            logger.write("Value at position %d in array \"soundeffects\" must be a string!\n", i);

            exit(EXIT_FAILURE);
        }

        std::shared_ptr<D2DSoundEffect> soundeffect(new D2DSoundEffect());

        D2DErrorContext ec("when loading soundeffect: ",
                           soundeffects[i].asCString());

        soundeffect->loadFromFile(soundeffects[i].asString());

        m_soundeffects[soundeffects[i].asString()] = soundeffect;
    }
}