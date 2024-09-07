#ifndef EVENTMANAGER_TPP
#define EVENTMANAGER_TPP

namespace TApp {
    template <EventType T>
    EventListenerId EventManager::addListener(const EventListener<T>& eventListener) {
        return getDispatcher<T>().addListener(eventListener);
    }

    template <EventType T>
    EventListener<T>* EventManager::getListener(EventListenerId id) {
        return getDispatcher<T>().getListener(id);
    }

    template <EventType T>
    bool EventManager::removeListener(EventListenerId id) {
        return getDispatcher<T>().removeListener(id);
    }

    template <EventType T>
    void EventManager::dispatch(T& event) {
        getDispatcher<T>().dispatch(event);
    }

    template <EventType T, typename... Args>
    void EventManager::dispatch(Args&&... args) {
        T event(std::forward<Args>(args)...);
        getDispatcher<T>().dispatch(event);
    }

    template <EventType T>
    EventDispatcher<T>& EventManager::getDispatcher() {
        size_t hash = typeid(T).hash_code();
        if (dispatchers.find(hash) == dispatchers.end()) {
            dispatchers[hash] = std::make_unique<EventDispatcher<T>>();
        }
        return *static_cast<EventDispatcher<T>*>(dispatchers[hash].get());
    }
}

#endif // EVENTMANAGER_TPP