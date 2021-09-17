#pragma once

typedef struct Entity
{
  int _0x3DC[247];
  float x, y, z;
  int _0x928[336];
  float hp;
} Entity;

typedef struct EntityObject
{
  struct Entity* entity;
} EntityObject;

typedef struct EntityList
{
  int _0x8[2];
  unsigned int n_entities;
  EntityObject ents[120];
} EntityList;

typedef struct PlayerCoords
{
  float x, y, z;
} PlayerCoords;
