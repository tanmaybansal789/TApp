#ifndef SINGLETON_TPP
#define SINGLETON_TPP

#include "Engine/Utils/Singleton/Singleton.h"

namespace TEngine_V2 {
    template <typename T>
    T& Singleton<T>::instance() {
        static T instance;
        return instance;
    }
}

#endif // SINGLETON_TPP