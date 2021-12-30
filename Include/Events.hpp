#ifndef EVENTS_HPP
#define EVENTS_HPP

#ifndef WIN32_LEAN_AND_MEAN
#   define WIN32_LEAN_AND_MEAN
#endif // WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace events {
    bool HandleKeyboard(void);
}

#endif // EVENTS_HPP
