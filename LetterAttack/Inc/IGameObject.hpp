/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include <SFML/Graphics.hpp>

class IGameObject
{
public:
	virtual bool onSpawn() { return true; }
	virtual bool onUpdate( float dt ) { return true; }
	virtual bool onKill() { return true; }
	virtual bool onEvent( const sf::Event& event ) { return true; }
	virtual bool onDraw( sf::RenderTarget& target ) { return true; }
	void kill() { die = true; }
	bool wantDie() { return die; }
	virtual const char* tag()
	{
		return "";
	}

private:
	bool die = false;
};