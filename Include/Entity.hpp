#ifndef ENTITY_HPP
#define ENTITY_HPP

struct Entity {
    int _0x3DC[247];
    float x;
    float y;
    float z;
    int _0x928[336];
    float hp;
};

struct EntityObject {
  Entity* entity;
};

struct EntityList {
  int _0x8[2];
  unsigned int n_entities;
  EntityObject ents[127];
};

struct Coords {
  float x;
  float y;
  float z;
};

#endif // ENTITY_HPP
