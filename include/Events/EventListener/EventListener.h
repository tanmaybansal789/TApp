#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

#include <functional>

namespace TApp {
    using EventListenerId = size_t;  // Generic ID not tied to event type.

    template <EventType T>
    using EventListener = std::function<void(T& event)>;  // Listener function still specific to event type.
}

#endif // EVENTLISTENER_H