#ifndef SINGLETON_H
#define SINGLETON_H

namespace TEngine_V2 {
    template <typename T>
    class Singleton {
    public:
        Singleton() = default;
        Singleton(const Singleton& other) = delete;
        Singleton(Singleton&& other) = delete;
        Singleton& operator=(const Singleton& other) = delete;

        static T& instance();
    };
}

#include "Engine/Utils/Singleton/Singleton.tpp"

#endif // SINGLETON_H