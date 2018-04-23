/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "Letter.hpp"

Letter::Letter( char letter, const sf::Vector2f& pos, const sf::Vector2f& vel, float yAccel )
{
	const static sf::Font& defaultFont = getDefaultFont();
	visualRepresentation.setFont( defaultFont );
	visualRepresentation.setString( letter );
	visualRepresentation.setPosition( pos );
	visualRepresentation.setFillColor( sf::Color::Red );
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
	if ( ev.type == sf::Event::KeyPressed )
		if ( ev.key.code == keyToPress )
			kill();

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

void Letter::letterToKey( char letter )
{
	const uint8_t keyNum = static_cast<uint8_t>( sf::Keyboard::Key::A ) + ( letter - 'A' );
	keyToPress = static_cast<sf::Keyboard::Key>( keyNum );
}
