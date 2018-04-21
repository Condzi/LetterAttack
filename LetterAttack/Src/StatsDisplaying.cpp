/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "StatsDisplaying.hpp"

#include "Font.hpp"

StatsDisplaying::StatsDisplaying( PlayerStats& stats ) :
	statsRef( stats )
{}

bool StatsDisplaying::onDraw( sf::RenderTarget& target )
{
	static auto& font = getDefaultFont();
	sf::Text score;
	score.setFont( font );
	score.setFillColor( sf::Color::Cyan );
	score.setString( std::to_string( statsRef.score ) );
	sf::Text lifes;
	lifes.setFont( font );
	lifes.setFillColor( sf::Color::Green );
	lifes.setString( std::to_string( statsRef.lifes ) );

	lifes.setPosition( 600 - lifes.getGlobalBounds().width, 0 );

	target.draw( score );
	target.draw( lifes );

	return true;
}
