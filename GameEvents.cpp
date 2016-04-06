#include "GameEvents.h"

GameEvents* GameEvents::_instance = NULL;
const size_t GameEvents::FLICHER_TIME = 1000;
const size_t GameEvents::UNDO_FLICKER_TIME = 100;

void GameEvents::update()
{
	_flickerLight();
}

void GameEvents::_flickerLight()
{
	if (0 == (rand() % GameEvents::FLICHER_TIME))
	{
		_world->flickerLight(true);
	}
	if (0 == (rand() % GameEvents::UNDO_FLICKER_TIME))
	{
		_world->flickerLight(false);
	}
}

