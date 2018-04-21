/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "Letter.hpp"

#include "Font.hpp"

Letter::Letter( char letter, const sf::Vector2f& pos, const sf::Vector2f& vel, float yAccel )
{
	visualRepresentation.setFont( getDefaultFont() );
	visualRepresentation.setString( letter );
	visualRepresentation.setPosition( pos );
	yAcceleration = yAccel;
	velocity = vel;
	letterToKey( letter );
}

sf::FloatRect Letter::getBounds()
{
	return visualRepresentation.getGlobalBounds();
}

bool Letter::onEvent( const sf::Event& ev )
{
	if ( ev.type == sf::Event::KeyReleased )
		if ( ev.key.code == keyToPress )
			wantToDie = true;

	return true;
}

bool Letter::onUpdate( float dt )
{
	visualRepresentation.move( velocity * dt );
	velocity.y += yAcceleration * dt;

	return true;
}

bool Letter::onDraw( sf::RenderTarget& target )
{
	target.draw( visualRepresentation );
	return true;
}

bool Letter::wantDie()
{
	return wantToDie;
}

void Letter::letterToKey( char letter )
{
	const uint8_t keyNum = static_cast<uint8_t>( sf::Keyboard::Key::A ) + ( letter - 'A' );
	keyToPress = static_cast<sf::Keyboard::Key>( keyNum );
}