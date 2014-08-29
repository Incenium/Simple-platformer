/*
===============================================================================
* File: D2DErrorContext.hpp
*
* Author: Andrew Killian
*
* Email: Inceniium@gmail.com
*
* Description: Describes the context in which an error might occur in a scoped
*              manner
===============================================================================
*/

#ifndef D2D_ERROR_CONTEXT
#define D2D_ERROR_CONTEXT

#include <cstdarg>

#include "D2DLogger.hpp"

void D2DWriteErrorContexts(D2DLogger& logger);
void D2DFail(D2DLogger& logger,  const char* format, ...);

class D2DErrorContext {
  public:
    D2DErrorContext(const char* name, const char* data);
    ~D2DErrorContext();
};

#endif