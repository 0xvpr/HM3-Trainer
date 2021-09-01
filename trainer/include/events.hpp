#pragma once

#include "entity.h"

namespace Events
{
	void UpdateStatus(void);

	void UpdateCurrentEntity(void);

	void UpdatePlayerCamCoords(void);

	void UpdateEntityList(EntityList* entityList);

	void HandleKeyboard(void);
};
