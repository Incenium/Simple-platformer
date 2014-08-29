#include "strutil.hpp"

std::vector<std::string> stringSplit(std::string toSplit,
                                     std::string delim)
{
    std::vector<std::string> results;
    std::size_t pos;
    
    while ((pos = toSplit.find(delim)) != std::string::npos){
        std::string field = toSplit.substr(0, pos);
        results.push_back(field);
        toSplit.erase(0, pos + 1);
    }

    results.push_back(toSplit);

    return results;
}
