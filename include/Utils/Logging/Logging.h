//
// Created by Tanmay Bansal on 29/08/2024.
//

#ifndef LOGGING_H
#define LOGGING_H

#include <iostream>
#include <string>
#include <cstdlib>

#define TAPP_INFO(message) std::cout << "[TAPP] INFO: " << message << std::endl
#define TAPP_WARN(message) std::cout << "[TAPP] WARN: " << message << std::endl
#define TAPP_ERROR(message) std::cerr << "[TAPP] ERROR: " << message << std::endl

#define TAPP_ASSERT(condition, message) \
    if (!(condition)) { \
        std::cerr << "[TAPP] ERROR - ASSERTION FAILED: " << message << std::endl; \
        std::abort(); \
    }

#define TAPP_STATIC_ASSERT(condition, message) static_assert(condition, message)

#endif //LOGGING_H
