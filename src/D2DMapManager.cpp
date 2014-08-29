// #include <fstream>

// #include "D2DError.hpp"
// #include "D2DMapManager.hpp"

// #include "json/json.h"

// D2DMapManager::D2DMapManager()
// {
//     m_logger.open();
// }

// void D2DMapManager::loadMaps(std::string maps)
// {
//     Json::Reader reader;
//     Json::Value root;

//     std::ifstream file;
//     std::string line;
//     std::string jsonToParse;

//     file.open(maps);
//     if (!file.is_open())
//         D2DFail(m_logger, "Unable to open maps data file %s\n", maps.c_str());

//     while (getline(file, line))
//         jsonToParse += line;

//     if(!reader.parse(jsonToParse, root)){
//         D2DFail(m_logger,
//                 "Unable to parse maps data file %s, Json reader error messages: %s\n", maps.c_str(), reader.getFormattedErrorMessages().c_str());
//     }

//     Json::Value maplist = root["maps"];

//     if (maplist == Json::Value::null){
//         D2DFail(m_logger, "Array \"maps\" missing in maps data file %s\n",
//                 maps.c_str());
//     }

//     for (int i = 0; i < maplist.size(); i++){
//         std::shared_ptr<>
//     }
// }