#include "hacks.hpp"

#include "assembly.hpp"
#include "patches.hpp"
#include "offsets.hpp"
#include "entity.hpp"
#include "memory.hpp"

#include <cmath>

extern uintptr_t g_module_base_addr;

[[nodiscard]]
static inline bool is_ingame() {
    auto entityList = *(EntityList **)(g_module_base_addr + offsets::entity);

    return entityList && ( entityList->n_entities > 7 && entityList->n_entities < 167 );
}

void hacks::teleport_to_cam() {
    auto player = memory::find_dynamic_address<Coords *>(g_module_base_addr + offsets::player_xyz, offsets::player_xyz_offsets);
    auto cam = memory::find_dynamic_address<Coords *>(g_module_base_addr + offsets::cam_xyz, offsets::cam_xyz_offsets);

    if (is_ingame()) {
        player->x = cam->x +  5;
        player->y = cam->y + 10;
        player->z = cam->z +  5;
    }

}

void hacks::teleport_to_entity(unsigned target) {
    auto player = memory::find_dynamic_address<Coords *>(g_module_base_addr + offsets::player_xyz, offsets::player_xyz_offsets);
    auto entityList = *(EntityList **)(g_module_base_addr + offsets::entity);
    auto entity = entityList->entities[target].entity;

    if (is_ingame() && entityList && entity) {
        player->x = entity->x +  5;
        player->y = entity->y +  5;
        player->z = entity->z +  5;
    }
}

void hacks::toggle_infinite_ammo(bool bEnabled) {
     void* ammo_addr         = (void *)(g_module_base_addr + offsets::ammo);
     void* clip_counter_addr = (void *)(g_module_base_addr + offsets::clip_counter);
     void* syr_poison_addr   = (void *)(g_module_base_addr + offsets::syr_poison);
     void* syr_sedative_addr = (void *)(g_module_base_addr + offsets::syr_sedative);

    if (bEnabled) {
        memory::patch(ammo_addr, patches::ammo_patch);
        memory::patch(clip_counter_addr, patches::clip_counter_patch);
        memory::patch(syr_poison_addr, patches::syr_poison_patch);
        memory::patch(syr_sedative_addr, patches::syr_sedative_patch);
    } else {
        memory::patch(ammo_addr, patches::ammo_original);
        memory::patch(clip_counter_addr, patches::clip_counter_original);
        memory::patch(syr_poison_addr, patches::syr_poison_original);
        memory::patch(syr_sedative_addr, patches::syr_sedative_original);
    }

}

void hacks::toggle_infinite_health(bool bEnabled) {
     void* health_addr = (void *)(g_module_base_addr + offsets::health);

    if (bEnabled) {
        memory::patch(health_addr, patches::health_patch);
    } else {
        memory::patch(health_addr, patches::health_original);
    }

}

void hacks::toggle_one_shot(bool bEnabled) {
     void* one_shot_addr = (void *)(g_module_base_addr + offsets::one_shot);

    if (bEnabled) {
        memory::patch(one_shot_addr, patches::one_shot_patch); // accidental kills no longer kill
    } else {
        memory::patch(one_shot_addr, patches::one_shot_original);
    }

}

void hacks::toggle_stealth(bool bEnabled) {
     void* stealth_addr = (void *)(g_module_base_addr + offsets::stealth);

    if (bEnabled) {
        memory::patch(stealth_addr, patches::stealth_patch);
    } else {
        memory::patch(stealth_addr, patches::stealth_original);
    }

}

void hacks::toggle_no_recoil(bool bEnabled) {
     void* recoil_addr = (void *)(g_module_base_addr + offsets::recoil);

    if (bEnabled) {
        memory::detour(recoil_addr, assembly::no_recoil, sizeof(patches::recoil_original));
    } else {
        memory::patch(recoil_addr, patches::recoil_original); 
    }

}

void hacks::toggle_flash(bool bEnabled) {
     void* speed_addr = (void *)(g_module_base_addr + offsets::speed);
     void* mul_addr   = (void *)(g_module_base_addr + offsets::mul);

    if (bEnabled) {
        memory::detour(speed_addr, assembly::speed, sizeof(patches::speed_original));
        memory::detour(mul_addr, assembly::mul, sizeof(patches::mul_original));
    } else {
        memory::patch(speed_addr, patches::speed_original); 
        memory::patch(mul_addr, patches::mul_original); 
    }

}

void hacks::kill_current_entity(unsigned target) {
    auto entityList = *(EntityList **)(g_module_base_addr + offsets::entity);

    if (is_ingame() && entityList) {
        auto ent = entityList->entities[target].entity;
        if (!ent) {
            return;
        }

        float force_vector_a[3] = { 1.f, 1.f, -1000.f };
        float force_vector_b[3] = { 1.f, 1.f,     1.f };
        ent->vtable->DieByForce(ent, force_vector_a, force_vector_b, 100.f, 100);
    }
}

void hacks::kill_target_in_crosshair() {
    auto entityList = *(EntityList **)(g_module_base_addr + offsets::entity);
    auto cam = memory::find_dynamic_address<Coords *>(g_module_base_addr + offsets::cam_xyz, offsets::cam_xyz_offsets);

    if (!entityList || !cam) {
        return;
    }

    if (is_ingame()) {
        size_t n_entities = entityList->n_entities;
        for (size_t i = 0; i < n_entities; ++i) {
            auto ent = entityList->entities[i].entity;
            if (!ent) {
                return;
            }

            auto square = [](float x) constexpr -> float { return x * x; };
            auto distance = std::sqrt(
                square(ent->x - cam->x) +
                square(ent->y - cam->y) +
                square(ent->z - cam->z)
            );

            if (distance < 100.f && ent->vtable->GetHealth(ent) > 0) {
                ent->vtable->ActivateRagdollOrAnim(ent);

                float force_vector_a[3] = { 1000.f, 1000.f, 1000.f };
                float force_vector_b[3] = { 1.f,       1.f, 1.f };
                ent->vtable->DieByForce(ent, force_vector_a, force_vector_b, 1.f, 1);
            }
        }
    }
}

// Testing, causes crashes for now
void hacks::disarm_everyone() {
    auto entityList = *(EntityList **)(g_module_base_addr + offsets::entity);

    if (is_ingame()) {
        size_t n_entities = entityList->n_entities; 
        for (size_t i = 0; i < n_entities; ++i) {
            auto ent = entityList->entities[i].entity;
            if (!ent) {
                return;
            }

            auto rhand_weapon = ent->vtable->GetRHandWeapon(ent);
            if (rhand_weapon) {
                ent->vtable->ControlDrop(ent, rhand_weapon);
            }
            auto rhand_item = ent->vtable->GetRHandItem(ent);
            if (rhand_item) {
                ent->vtable->ControlDrop(ent, rhand_item);
            }

            auto lhand_weapon = ent->vtable->GetLHandWeapon(ent);
            if (lhand_weapon) {
                ent->vtable->ControlDrop(ent, lhand_weapon);
            }
            auto lhand_item = ent->vtable->GetLHandItem(ent);
            if (lhand_item) {
                ent->vtable->ControlDrop(ent, lhand_item);
            }
        }
    }
}
