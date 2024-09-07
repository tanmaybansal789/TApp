#ifndef EVENTDISPATCHER_TPP
#define EVENTDISPATCHER_TPP

#define TAPP_CHECK_LISTENER_EXISTS

namespace TApp {
    template <EventType T>
    EventListenerId EventDispatcher<T>::addListener(const EventListener<T>& eventListener) {
        EventListenerId id;
        if (freedIds.empty()) {
            id = nextId++;
        } else {
            id = freedIds.front();
            freedIds.pop();
        }
        eventListeners[id] = eventListener;
        return id;
    }

    template <EventType T>
    EventListener<T>* EventDispatcher<T>::getListener(EventListenerId id) {
        auto it = eventListeners.find(id);
        return it != eventListeners.end() ? &it->second : nullptr;
    }

    template <EventType T>
    bool EventDispatcher<T>::removeListener(EventListenerId id) {
        auto it = eventListeners.find(id);
#ifdef TAPP_CHECK_LISTENER_EXISTS
        if (it == eventListeners.end()) {
            return false;
        }
#endif
        eventListeners.erase(it);
        freedIds.push(id);
        return true;
    }

    template <EventType T>
    void EventDispatcher<T>::dispatch(T& event) {
        for (auto& [id, listener] : eventListeners) {
            if (event.isHandled()) break;
            listener(event);
        }
    }
}

#endif //EVENTDISPATCHER_TPP
