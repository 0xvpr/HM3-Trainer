#ifndef EVENTS_HEADER
#define EVENTS_HEADER

#include <cstdint>

namespace events {

class event_handler {
    virtual void run() = 0;
};

} // namespace events

#endif // EVENTS_HEADER
