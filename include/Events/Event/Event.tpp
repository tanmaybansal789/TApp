#ifndef EVENT_TPP
#define EVENT_TPP

#define TAPP_CHECK_EVENT_EXISTS

namespace TApp {
    template <typename... Args>
    consteval EventScope_t makeEventScopes(Args... scopes) {
        TAPP_STATIC_ASSERT((std::is_same_v<Args, EventScope> && ...), "All arguments to makeEventScope must be of type EventScope");
        return (scopes | ...);
    }

    // Event implementation
    constexpr EventScope_t Event::getScopes() const {
        return scopes;
    }

    constexpr bool Event::inScope(EventScope scope) const {
        return (scopes & static_cast<EventScope_t>(scope)) != 0;
    }

    constexpr bool Event::scopesInclude(EventScope_t otherScopes) const {
        return (scopes & otherScopes) == otherScopes;
    }

    constexpr bool Event::scopesIncludedIn(EventScope_t otherScopes) const {
        return (otherScopes & scopes) == scopes;
    }
}

#endif // EVENT_TPP