#include "hacks.hpp"

#include "assembly.hpp"
#include "offsets.hpp"
#include "entity.hpp"
#include "memory.hpp"

#include <cmath>

extern uintptr_t module_base_addr;

[[nodiscard]]
static inline bool IsInGame() {
    auto entityList = *(EntityList **)(module_base_addr + offsets::entity);

    return !entityList || ( entityList->n_entities > 7 && entityList->n_entities < 167 );
}

void hacks::TeleportToCam() {
    auto player = memory::FindDynamicAddress<Coords *>(module_base_addr + offsets::player_xyz, offsets::player_xyz_offsets);
    auto cam = memory::FindDynamicAddress<Coords *>(module_base_addr + offsets::cam_xyz, offsets::cam_xyz_offsets);

    if (IsInGame()) {
        player->x = cam->x +  5;
        player->y = cam->y + 10;
        player->z = cam->z +  5;
    }

}

void hacks::TeleportToEntity(unsigned target) {
    auto player = memory::FindDynamicAddress<Coords *>(module_base_addr + offsets::player_xyz, offsets::player_xyz_offsets);
    auto entityList = *(EntityList **)(module_base_addr + offsets::entity);
    auto entity = entityList->entities[target].entity;

    if (IsInGame()) {
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

    if (IsInGame()) {
        auto ent = entityList->entities[target].entity;
        float force_vector_a[3] = { 0.f, 0.f, -1000.f };
        float force_vector_b[3] = { 0.f, 0.f, 1000.f };
        ent->vtable->DieByForce(ent, force_vector_a, force_vector_b, 100, 1);
    }
}

void hacks::KillTargetInCrosshair() {
    auto entityList = *(EntityList **)(module_base_addr + offsets::entity);
    auto cam = memory::FindDynamicAddress<Coords *>(module_base_addr + offsets::cam_xyz, offsets::cam_xyz_offsets);

    if (!entityList || !cam) {
        return;
    }

    if (IsInGame()) {
        size_t n_entities = entityList->n_entities;
        for (size_t i = 0; i < n_entities; ++i) {
            auto ent = entityList->entities[i].entity;
            if (!ent) 
            {
                continue;
            }

            if (std::fabs(cam->x - ent->x) < 50.f && std::fabs(cam->y - ent->y) < 50.f) {
                float force_vector_a[3] = { 0.f, 0.f, -1000.f };
                float force_vector_b[3] = { 0.f, 0.f, 1000.f };
                ent->vtable->DieByForce(ent, force_vector_a, force_vector_b, 100, 1);
            }
        }
    }
}

void hacks::KillEveryone() {
    auto player = memory::FindDynamicAddress<Coords *>(module_base_addr + offsets::player_xyz, offsets::player_xyz_offsets);
    auto entityList = *(EntityList **)(module_base_addr + offsets::entity);

    if (IsInGame()) {
        size_t n_entities = entityList->n_entities; 
        Coords player_original_pos = { player->x, player->y, player->z };

        for (size_t i = 0; i < n_entities; ++i) {
            auto ent = entityList->entities[i].entity;

            if ( /* ent->vtable->IsAwake(ent) | ent->vtable->IsVisible(ent) */ ent->vtable->GetWeapon(ent) == 0) {
                player->x = ent->x +  5;
                player->y = ent->y + 10;
                player->z = ent->z +  5;

                float force_vector_a[3] = { 0.f, 0.f, -1000.f };
                float force_vector_b[3] = { 0.f, 0.f, 1000.f };
                ent->vtable->DieByForce(ent, force_vector_a, force_vector_b, 100, 1);
            }
        }

        player->x = player_original_pos.x;
        player->y = player_original_pos.y;
        player->z = player_original_pos.z;
    }
}
