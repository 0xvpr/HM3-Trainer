#ifndef HACKS_HEADER
#define HACKS_HEADER

namespace hacks {

void teleport_to_cam(void);
void teleport_to_entity(unsigned target);
void toggle_infinite_ammo(bool bEnabled);
void toggle_infinite_health(bool bEnabled);
void toggle_one_shot(bool bEnabled);
void toggle_stealth(bool bEnabled);
void toggle_no_recoil(bool bEnabled);
void toggle_flash(bool bEnabled);
void kill_current_entity(unsigned target);
void kill_target_in_crosshair(void);
void disarm_everyone(void);

} // namespace hacks

#endif // HACKS_HEADER
