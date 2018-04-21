/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include "IGameObject.hpp"

class Letter final :
	public IGameObject
{
public:
	Letter( char letter, const sf::Vector2f& pos, const sf::Vector2f& vel, float yAccel );

	sf::FloatRect getBounds();

	bool onEvent( const sf::Event& ev ) override;
	bool onUpdate( float dt ) override;
	bool onDraw( sf::RenderTarget& target ) override;
	bool wantDie() override;

	const char* tag() override
	{
		return "Letter";
	}

private:
	inline static sf::Font* font = nullptr;
	bool wantToDie = false;
	sf::Keyboard::Key keyToPress;
	float yAcceleration = 0;
	sf::Vector2f velocity;
	sf::Text visualRepresentation;

	void letterToKey( char letter );
};