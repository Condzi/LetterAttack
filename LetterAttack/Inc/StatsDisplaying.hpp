/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include "IGameObject.hpp"
#include "PlayerStats.hpp"

class StatsDisplaying final :
	public IGameObject
{
public:
	StatsDisplaying( PlayerStats& stats );

	const char* tag() override
	{
		return "StatsDisplaying";
	}

	bool onDraw( sf::RenderTarget& target );

private:
	PlayerStats& statsRef;
};