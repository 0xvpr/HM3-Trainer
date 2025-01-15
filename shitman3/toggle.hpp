#ifndef   TOGGLE_HEADER
#define   TOGGLE_HEADER

#include <atomic>

namespace toggle {

class toggleable {
    [[nodiscard]] virtual bool is_active() const = 0;
    [[nodiscard]] virtual bool toggle()    const = 0;
public:
    mutable std::atomic<bool> is_active_ = false;
};

} // namespace toggle

#endif // TOGGLE_HEADER
