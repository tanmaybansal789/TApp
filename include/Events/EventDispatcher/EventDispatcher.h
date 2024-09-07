#ifndef EVENTDISPATCHER_H
#define EVENTDISPATCHER_H

#include "Events/Event/Event.h"
#include "Events/EventListener/EventListener.h"

namespace TApp {
    class IEventDispatcher {
    public:
        virtual ~IEventDispatcher() = default;
    };

    template <EventType T>
    class EventDispatcher : public IEventDispatcher {
    public:
        EventListenerId addListener(const EventListener<T>& eventListener);
        EventListener<T>* getListener(EventListenerId id);
        bool removeListener(EventListenerId id);
        void dispatch(T& event);

    private:
        std::unordered_map<EventListenerId, EventListener<T>> eventListeners;
        std::queue<EventListenerId> freedIds;
        EventListenerId nextId = 0;
    };
}

#include "Events/EventDispatcher/EventDispatcher.tpp"

#endif // EVENTDISPATCHER_H