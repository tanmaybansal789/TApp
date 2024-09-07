#ifndef SINGLETON_TPP
#define SINGLETON_TPP

namespace TApp {
    template <typename T>
    T& Singleton<T>::instance() {
        static T instance;
        return instance;
    }
}

#endif // SINGLETON_TPP