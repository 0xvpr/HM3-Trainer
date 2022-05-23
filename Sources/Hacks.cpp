#include "Hacks.hpp"

#include "Memory.hpp"
#include "Entity.hpp"
#include "Offsets.hpp"
#include "Assembly.hpp"

#include <math.h>

extern uintptr_t module_base_addr;

void hacks::TeleportToCam() {

    auto player = memory::FindDynamicAddress<Coords *>(module_base_addr + offsets::player_xyz, offsets::player_xyz_offsets);
    auto entityList = *(EntityList **)(module_base_addr + offsets::entity);
    auto cam = memory::FindDynamicAddress<Coords *>(module_base_addr + offsets::cam_xyz, offsets::cam_xyz_offsets);

    auto bInGame = [&entityList]{
        return entityList->n_entities > 7 && entityList->n_entities < 167;
    }();

    if (bInGame) {
        player->x = cam->x +  5;
        player->y = cam->y + 10;
        player->z = cam->z +  5;
    }

}

void hacks::TeleportToEntity(unsigned target) {

    auto player = memory::FindDynamicAddress<Coords *>(module_base_addr + offsets::player_xyz, offsets::player_xyz_offsets);
    auto entityList = *(EntityList **)(module_base_addr + offsets::entity);
    auto entity = entityList->entities[target].entity;

    auto bInGame = [&entityList]{
        return entityList->n_entities > 7 && entityList->n_entities < 167;
    }();

    if (bInGame) {
        player->x = entity->x +  5;
        player->y = entity->y + 10;
        player->z = entity->z +  5;
    }

}

void hacks::ToggleInfiniteAmmo(bool bEnabled) {

    static void* ammo_addr = (void *)(module_base_addr + offsets::ammo);
    static void* clip_counter_addr = (void *)(module_base_addr + offsets::clip_counter);

    static unsigned char ammo_original[1] = {
        0x49 // dec     eax
    };
    static unsigned char ammo_patch[1] = {
        0x40 // 
    };

    static unsigned char clip_counter_original[6] {
        0xFF, 0x8E, 0x9C, 0x00, 0x00, 0x00 // dec   [esi + 0x9C]
    };
    static unsigned char clip_counter_patch[6] {
        0x90, // nop
        0x90, // nop
        0x90, // nop
        0x90, // nop
        0x90, // nop
        0x90  // nop
    };

    if (bEnabled) {
        memory::Patch(ammo_addr, ammo_patch, sizeof(ammo_patch));
        memory::Patch(clip_counter_addr, clip_counter_patch, sizeof(clip_counter_patch));
    } else {
        memory::Patch(ammo_addr, ammo_original, sizeof(ammo_original));
        memory::Patch(clip_counter_addr, clip_counter_original, sizeof(clip_counter_original));
    }

}
void hacks::ToggleInfiniteHealth(bool bEnabled) {

    static void* health_addr = (void *)(module_base_addr + offsets::health);

    static unsigned char health_original[4] = {
        0xD8, 0x64, 0x24, 0x08
    };
    static unsigned char health_patch[4] = {
        0x90,
        0x90,
        0x90,
        0x90
    };

    if (bEnabled) {
        memory::Patch(health_addr, health_patch, sizeof(health_patch));
    } else {
        memory::Patch(health_addr, health_original, sizeof(health_original));
    }

}

void hacks::ToggleOneShot(bool bEnabled) {

    static void* one_shot_addr = (void *)(module_base_addr + offsets::one_shot);

    static unsigned char one_shot_original[10] = {
        0xD8, 0x64, 0x24, 0x04, 0xD9, 0x91, 0x28, 0x09, 0x00, 0x00
    };
    static unsigned char one_shot_patch[10] = {
        0xD8, 0xA1, 0x28, 0x09, 0x00, 0x00,
        0x90,
        0x90,
        0x90,
        0x90
    };

    if (bEnabled) {
        memory::Patch(one_shot_addr, one_shot_patch, sizeof(one_shot_patch)); // accidental kills no longer kill
    } else {
        memory::Patch(one_shot_addr, one_shot_original, sizeof(one_shot_original));
    }

}

void hacks::ToggleStealth(bool bEnabled) {

    static void* stealth_addr = (void *)(module_base_addr + offsets::stealth);

    static unsigned char stealth_original[2] = {
        0x3B, 0xC3 // cmp   eax, ebx
    };

    static unsigned char stealth_patch[2] = {
        0x39, 0xC0 // cmp   eax, eax
    };

    if (bEnabled) {
        memory::Patch(stealth_addr, stealth_patch, sizeof(stealth_patch));
    } else {
        memory::Patch(stealth_addr, stealth_original, sizeof(stealth_original));
    }

}

void hacks::ToggleNoRecoil(bool bEnabled) {

    static void* recoil_addr = (void *)(module_base_addr + offsets::recoil);
    static void* no_recoil_tramp_addr = (void *)NoRecoilTramp;

    static unsigned char recoil_original[6] = {
        0xD9, 0x99, 0xF8, 0x00, 0x00, 0x00
    };

    if (bEnabled) {
        memory::Detour(recoil_addr, no_recoil_tramp_addr, sizeof(recoil_original));
    } else {
        memory::Patch(recoil_addr, recoil_original, sizeof(recoil_original)); 
    }

}

void hacks::ToggleFlash(bool bEnabled) {

    static void* mul_addr   = (void *)(module_base_addr + offsets::mul);
    static void* mul_func   = (void *)(Multiplier);

    static void* speed_addr = (void *)(module_base_addr + offsets::speed);
    static void* flash_func = (void *)(Flash);

    static unsigned char mul_original[7] = {
        0xC7, 0x46, 0x14, 0x00, 0x00, 0x80, 0x3F // mov     [esi + 0x14], 3F800000
    };
    static unsigned char speed_original[6] = {
        0xD9, 0x59, 0x24,                        // fstp    dword ptr [ecx + 0x24]
        0xC2, 0x04, 0x00                         // ret     4
    };

    if (bEnabled) {
        memory::Detour(speed_addr, flash_func, sizeof(speed_original));
        memory::Detour(mul_addr, mul_func, sizeof(mul_original));
    } else {
        memory::Patch(speed_addr, speed_original, sizeof(speed_original)); 
        memory::Patch(mul_addr, mul_original, sizeof(mul_original)); 
    }

}

void hacks::KillCurrentEntity(unsigned target) {

    auto entityList = *(EntityList **)(module_base_addr + offsets::entity);

    auto bInGame = [&entityList]{
        return entityList->n_entities > 7 && entityList->n_entities < 167;
    }();

    if (bInGame) {
        auto ent = entityList->entities[target].entity;
        ent->vtable->Die(ent);
    }
}

void hacks::KillTargetInCrosshair(void) {

    auto entityList = *(EntityList **)(module_base_addr + offsets::entity);
    auto cam = memory::FindDynamicAddress<Coords *>(module_base_addr + offsets::cam_xyz, offsets::cam_xyz_offsets);

    auto bInGame = [&entityList]{
        return entityList->n_entities > 7 && entityList->n_entities < 167;
    }();

    if (bInGame) {
        size_t n_entities = entityList->n_entities;
        for (size_t i = 0; i < n_entities; ++i) {
            auto ent = entityList->entities[i].entity;
            if (fabs(cam->x - ent->x) < 50.f && fabs(cam->y - ent->y) < 50.f) {
                ent->vtable->Die(ent);
            }
        }
    }

}

void hacks::KillEveryone(void) {

    auto entityList = *(EntityList **)(module_base_addr + offsets::entity);

    auto bInGame = [&entityList]() {
        return (entityList->n_entities > 7 && entityList->n_entities < 167);
    };

    if (bInGame()) {
        size_t n_entities = entityList->n_entities; 
        for (size_t i = 0; i < n_entities; ++i) {
            auto ent = entityList->entities[i].entity;
            if (ent->vtable->IsVisible(ent)) {
                ent->vtable->Die(ent);
            }
        }
    }

}
