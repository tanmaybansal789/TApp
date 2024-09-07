#ifndef SINGLETON_H
#define SINGLETON_H

namespace TApp {
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

#include "Utils/Memory/Singleton/Singleton.tpp"

#endif // SINGLETON_H