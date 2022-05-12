#include "Offsets.hpp"
#include "Entity.hpp"
#include "Hacks.hpp"
#include "Memory.hpp"

extern uintptr_t module_base_addr;

void hacks::TeleportToCam() {

    auto player = memory::FindDynamicAddress<Coords *>(module_base_addr + offsets::player_xyz_addr, offsets::player_xyz_offsets);
    auto cam = memory::FindDynamicAddress<Coords *>(module_base_addr + offsets::cam_xyz_addr, offsets::cam_xyz_offsets);

    auto bInGame = []{
        auto entityList = *(EntityList **)(module_base_addr + offsets::entity_addr);
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

void hacks::ToggleGodMode(bool bEnabled) {

    char* ammo_op_codes            = (char*)"\x49";
    char* health_op_codes          = (char*)"\xD8\x64\x24\x08";
    char* one_shot_op_codes        = (char*)"\xD8\x64\x24\x04\xD9\x91\x28\x09\x00\x00";

    char* ammo_op_codes_new        = (char *)"\x40";
    char* health_op_codes_new      = (char *)"\x90\x90\x90\x90";
    char* one_shot_op_codes_new    = (char *)"\xD8\xA1\x28\x09\x00\x00\x90\x90\x90\x90";

    char* ammo_address             = (char *)offsets::ammo_addr;
    char* health_address           = (char *)offsets::health_addr;
    char* one_shot_address         = (char *)offsets::one_shot_addr;

    size_t ammo_op_code_length     = 1;
    size_t health_op_code_length   = 4;
    size_t one_shot_op_code_length = 10;

    if (bEnabled) {
        memory::Patch(ammo_address, ammo_op_codes_new, ammo_op_code_length);
        memory::Patch(health_address, health_op_codes_new, health_op_code_length);
        memory::Patch(one_shot_address, one_shot_op_codes_new, one_shot_op_code_length); // accidental kills no longer kill
    } else {
        memory::Patch(ammo_address, ammo_op_codes, ammo_op_code_length);
        memory::Patch(health_address, health_op_codes, health_op_code_length);
        memory::Patch(one_shot_address, one_shot_op_codes, one_shot_op_code_length); // accidental kills no longer kill
    }

}

void hacks::ToggleStealth(bool bEnabled) {

    static uintptr_t stealth_addr = module_base_addr + offsets::stealth_addr;

    static unsigned char stealth_original[2] = {
        0x3B, 0xC3 // cmp   eax, ebx
    };

    static unsigned char stealth_patch[2] = {
        0x39, 0xC0 // cmp   eax, eax
    };

    if (bEnabled) {
        memory::Patch((void *)stealth_addr, stealth_patch, sizeof(stealth_patch));
    } else {
        memory::Patch((void *)stealth_addr, stealth_original, sizeof(stealth_original));
    }

}
