#include "events.h"
#include <spdlog/spdlog.h>

class EventDispatcher {
public:
    static void Dispatch(DomainEvent& event) {
        spdlog::info("[DISPATCHER] Dispatching event: {}", event.GetName());

        if (const auto& feeding_event = dynamic_cast<FeedingTimeEvent*>(&event)) {
            feeding_event->Print();
        } else if (const auto& move_event = dynamic_cast<AnimalMoveEvent*>(&event)) {
            move_event->Print();
        } else {
            spdlog::warn("[DISPATCHER] Shit happens.");
        }
    }
};