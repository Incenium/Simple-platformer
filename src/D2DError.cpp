#include <iostream>
#include <stack>
#include <vector>

#include "D2DError.hpp"

static std::vector<const char*> D2DErrorContextName;
static std::vector<const char*> D2DErrorContextData;

void D2DWriteErrorContexts(D2DLogger& logger)
{
    for (int i = 0; i < D2DErrorContextName.size(); i++){
        logger.write("%s%s\n", D2DErrorContextName[i], D2DErrorContextData[i]);
    }
}

void D2DFail(D2DLogger& logger, const char* format, ...)
{
    D2DWriteErrorContexts(logger);

    va_list args;
    
    va_start(args, format);
    logger.write(format, args);
    va_end(args);

    exit(EXIT_FAILURE);
}

D2DErrorContext::D2DErrorContext(const char* name, const char* data)
{
    D2DErrorContextName.push_back(name);
    D2DErrorContextData.push_back(data);
}

D2DErrorContext::~D2DErrorContext()
{
    D2DErrorContextName.pop_back();
    D2DErrorContextData.pop_back();
}