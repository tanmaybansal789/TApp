#ifndef EVENT_H
#define EVENT_H

#include <cstdint>
#include <limits>

#define BIT(x) (1 << x)

namespace TApp {

    using EventScope_t = uint8_t;

    enum EventScope : EventScope_t {
        WindowScope = BIT(0),
        ApplicationScope = BIT(1),
        ExternalScope = BIT(2)
    };

    using EventId = size_t;
    constexpr size_t NULL_EVENT_ID = std::numeric_limits<size_t>::max();

    // Helper function to create a scope from multiple scopes
    template <typename... Args>
    consteval EventScope_t makeEventScopes(Args... args);
    class Event {
    public:
        explicit Event(EventScope_t scope) : scopes(scope), handled(false) {}
        virtual ~Event() = default;

        constexpr EventScope_t getScopes() const;
        constexpr bool inScope(EventScope scope) const;
        constexpr bool scopesInclude(EventScope_t otherScopes) const;
        constexpr bool scopesIncludedIn(EventScope_t otherScopes) const;

        void handle() { handled = true; }
        bool isHandled() const { return handled; }

    protected:
        EventScope_t scopes;
        bool handled;
    };

    template <typename T>
    concept EventType = std::is_base_of_v<Event, T>;
}

#include "Events/Event/Event.tpp"

#endif // EVENT_H