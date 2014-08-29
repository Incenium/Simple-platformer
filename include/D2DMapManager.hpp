/*
===============================================================================
* File: D2DMapManager.hpp
*
* Author: Andrew Killian
*
* Email: Inceniium@gmail.com
*
* Description: Manages all the maps of the game
===============================================================================
*/

#ifndef D2D_MAP_MANAGER
#define D2D_MAP_MANAGER

#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include "D2DError.hpp"
#include "D2DMapManager.hpp"

#include "json/json.h"

template <class T>
class D2DMapManager {
  public:
    D2DMapManager()
    {
        m_logger.open();
    };
    
    void loadMaps(std::string maps)
    {
        Json::Reader reader;
        Json::Value root;

        std::ifstream file;
        std::string line;
        std::string jsonToParse;

        file.open(maps);
        if (!file.is_open()){
            D2DFail(m_logger, "Unable to open maps data file %s\n",
                    maps.c_str());
        }

        while (getline(file, line))
            jsonToParse += line;

        if(!reader.parse(jsonToParse, root)){
            D2DFail(m_logger,
                    "Unable to parse maps data file %s, Json reader error messages: %s\n", maps.c_str(), reader.getFormattedErrorMessages().c_str());
        }

        Json::Value maplist = root["maps"];

        if (maplist == Json::Value::null){
            D2DFail(m_logger, "Array \"maps\" missing in maps data file %s\n",
                    maps.c_str());
        }

        for (int i = 0; i < maplist.size(); i++){
            //std::shared_ptr<D2DLevel> level(new T);
        }
    };

  private:
    //std::vector<std::shared_ptr<D2DMap>> m_maps;
    int m_currentmap;

    D2DLogger m_logger;
};

#endif