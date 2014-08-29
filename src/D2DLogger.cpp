#include <iostream>

#include "D2DLogger.hpp"

D2DLogger::D2DLogger()
{
}

D2DLogger::~D2DLogger()
{
    file.close();
}

// TODO: make D2DLogger::open open file in append mode
void D2DLogger::open(const std::string& path)
{
    file.open(path, std::ios::app);

    if (!file.is_open()){
        std::cout << "Unable to open log file " << path << " for writing!"
                  << std::endl;

        exit(EXIT_FAILURE);
    }
}

void D2DLogger::write(const char* format, ...)
{
    // va_list args;
    // va_start(args, format);

    // while (*format != '\0'){
    //     if (*format == '%'){
    //         if (*++format == 's'){
    //             const char* string = va_arg(args, const char*);
    //             std::cout << string;
    //             file << string;

    //             ++format;
    //         }

    //         else if (*format == 'd'){
    //             int i = va_arg(args, int);
    //             std::cout << i;

    //             file << i;

    //             ++format;
    //         }

    //         else if (*format == 'f'){
    //             double d = va_arg(args, double);
    //             std::cout << d;

    //             file << d;

    //             ++format;
    //         }

    //         else if (*format == '%'){
    //             std::cout << *format;

    //             file << *format;

    //             ++format;
    //         }
    //     }

    //     else {
    //         std::cout << *format;

    //         file << *format++;
    //     }
    // }

    // file << std::endl;
    
    // va_end(args);

    va_list args;
    va_start(args, format);

    write(format, args);

    va_end(args);
}

void D2DLogger::write(const char* format, va_list args)
{
    while (*format != '\0'){
        if (*format == '%'){
            if (*++format == 's'){
                const char* string = va_arg(args, const char*);
                std::cout << string;
                file << string;

                ++format;
            }

            else if (*format == 'd'){
                int i = va_arg(args, int);
                std::cout << i;

                file << i;

                ++format;
            }

            else if (*format == 'f'){
                double d = va_arg(args, double);
                std::cout << d;

                file << d;

                ++format;
            }

            else if (*format == '%'){
                std::cout << *format;

                file << *format;

                ++format;
            }
        }

        else {
            std::cout << *format;

            file << *format++;
        }
    }

    file << std::endl;
}