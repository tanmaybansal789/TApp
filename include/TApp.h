
#ifndef TAPP_H
#define TAPP_H

// Utils headers
#include "Utils/Memory/PoolAllocator/PoolAllocator.h"
#include "Utils/Memory/PoolAllocator/PoolAllocator.tpp"

#include "Utils/Memory/Singleton/Singleton.h"
#include "Utils/Memory/Singleton/Singleton.tpp"

#include "Utils/Logging/Logging.h"
       
// Layers headers
#include "Layers/Layer/Layer.h"
       
#include "Layers/LayerStack/LayerStack.h"
#include "Layers/LayerStack/LayerStack.tpp"

// Window headers
#include "Window/Window.h"
#include "Window/WindowEvents.h"
#include "Window/WindowSettings.h"

// Event headers
#include "Events/Event/Event.h"
#include "Events/Event/Event.tpp"

#include "Events/EventListener/EventListener.h"

#include "Events/EventDispatcher/EventDispatcher.h"
#include "Events/EventDispatcher/EventDispatcher.tpp"

#include "Events/EventManager/EventManager.h"
#include "Events/EventManager/EventManager.tpp"

// Input headers
#include "Input/InputEvents.h"

// Application headers
#include "Application/Application.h"

#endif //TAPP_H
