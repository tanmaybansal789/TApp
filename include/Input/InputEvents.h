#ifndef INPUTEVENTS_H
#define INPUTEVENTS_H

#include "Events/Event/Event.h"

namespace TApp {
    namespace InternalEvents {
        class KeyEvent : public Event {
        public:
            KeyEvent()
                : Event(makeEventScopes(WindowScope)) {}

            KeyEvent(int key, int scancode, int action, int mods)
                : key(key), scancode(scancode), action(action), mods(mods), Event(makeEventScopes(WindowScope)) {}

            // Getters
            int getKey() const { return key; }
            int getScancode() const { return scancode; }
            int getAction() const { return action; }
            int getMods() const { return mods; }

        private:
            int key, scancode, action, mods;

        };

        class MouseButtonEvent : public Event {
        public:
            MouseButtonEvent(int button, int action, int mods)
                : button(button), action(action), mods(mods), Event(makeEventScopes(WindowScope)) {}

            // Getters
            int getButton() const { return button; }
            int getAction() const { return action; }
            int getMods() const { return mods; }

        private:
            int button, action, mods;
        };
    }
}


#endif //INPUTEVENTS_H
