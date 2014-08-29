/*
===============================================================================
* File: D2DLogger.hpp
*
* Author: Andrew Killian
*
* Email: Inceniium@gmail.com
*
* Description: Logs information to a given file
===============================================================================
*/

#ifndef D2D_LOGGER
#define D2D_LOGGER

#include <cstdarg>
#include <fstream>
#include <string>

class D2DLogger {
  public:
    D2DLogger();
    ~D2DLogger();

    void open(const std::string& path="stdout.log");
    void write(const char* format, ...);
    void write(const char* format, va_list args);

  private:
    std::ofstream file;
};

#endif