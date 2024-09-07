#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <unordered_map>

#include "Events/Event/Event.h"
#include "Events/EventListener/EventListener.h"
#include "Events/EventDispatcher/EventDispatcher.h"

namespace TApp {
    class EventManager {
    public:
        template <EventType T>
        EventListenerId addListener(const EventListener<T>& eventListener);

        template <EventType T>
        EventListener<T>* getListener(EventListenerId id);

        template <EventType T>
        bool removeListener(EventListenerId id);

        template <EventType T>
        void dispatch(T& event);

        template <EventType T, typename... Args>
        void dispatch(Args&&... args);

    private:
        template <EventType T>
        EventDispatcher<T>& getDispatcher();

        std::unordered_map<size_t, std::unique_ptr<IEventDispatcher>> dispatchers;
    };
}

#include "Events/EventManager/EventManager.tpp"

#endif // EVENTMANAGER_H