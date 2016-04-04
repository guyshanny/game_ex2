#pragma once

#include "World.h"

class GameEvents
{
public:
	static GameEvents* instance()
	{
		if (NULL == _instance)
		{
			_instance = new GameEvents();
		}
		return _instance;
	}
	void init(World* world) { _world = world; }

	void update();

	/************************************************************************/
	/* Time based events                                                    */
	/************************************************************************/
	// Flickering
	static const size_t FLICHER_TIME;
	static const size_t UNDO_FLICKER_TIME;
	



private:
	GameEvents() {}
	static GameEvents* _instance;
	World* _world;

	// Events
	void _flickerLight();

};