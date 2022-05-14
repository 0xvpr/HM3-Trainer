#include "Offsets.hpp"
#include "Entity.hpp"
#include "Hacks.hpp"
#include "Memory.hpp"

extern uintptr_t module_base_addr;

void hacks::TeleportToCam() {

    auto player = memory::FindDynamicAddress<Coords *>(module_base_addr + offsets::player_xyz_addr, offsets::player_xyz_offsets);
    auto entityList = *(EntityList **)(module_base_addr + offsets::entity_addr);
    auto cam = memory::FindDynamicAddress<Coords *>(module_base_addr + offsets::cam_xyz_addr, offsets::cam_xyz_offsets);

    auto bInGame = [&entityList]{
        return entityList->n_entities > 1 && entityList->n_entities < 167;
    }();

    if (bInGame) {
        player->x = cam->x +  5;
        player->y = cam->y + 10;
        player->z = cam->z +  5;
    }

}

void hacks::TeleportToEntity(unsigned target) {

    auto player = memory::FindDynamicAddress<Coords *>(module_base_addr + offsets::player_xyz_addr, offsets::player_xyz_offsets);
    auto entityList = *(EntityList **)(module_base_addr + offsets::entity_addr);
    auto entity = entityList->ents[target].entity;

    auto bInGame = [&entityList]{
        //auto entityList = *(EntityList **)(module_base_addr + offsets::entity_addr);
        return entityList->n_entities > 1 && entityList->n_entities < 167;
    }();

    if (bInGame) {
        player->x = entity->x +  5;
        player->y = entity->y + 10;
        player->z = entity->z +  5;
    }

}

void hacks::ToggleInfiniteAmmo(bool bEnabled) {

    static void* ammo_addr = (void *)(module_base_addr + offsets::ammo_addr);

    static unsigned char ammo_original[1] = {
        0x49
    };
    static unsigned char ammo_patch[1] = {
        0x40
    };

    if (bEnabled) {
        memory::Patch(ammo_addr, ammo_patch, sizeof(ammo_patch));
    } else {

        memory::Patch(ammo_addr, ammo_original, sizeof(ammo_original));
    }

}
void hacks::ToggleInfiniteHealth(bool bEnabled) {

    static void* health_addr = (void *)(module_base_addr + offsets::health_addr);

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

    static void* one_shot_addr = (void *)(module_base_addr + offsets::one_shot_addr);

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

    static void* stealth_addr = (void *)(module_base_addr + offsets::stealth_addr);

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
