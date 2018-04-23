/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "StatsDisplaying.hpp"

#include "Font.hpp"

StatsDisplaying::StatsDisplaying( PlayerStats& stats ) :
	statsPtr( &stats )
{}

bool StatsDisplaying::onDraw( sf::RenderTarget& target )
{
	static auto& font = getDefaultFont();
	auto& statsRef = *statsPtr;
	sf::Text score;
	score.setFont( font );
	score.setFillColor( sf::Color::Cyan );
	score.setString( std::to_string( statsRef.score * 100 ) );
	sf::Text lifes;
	lifes.setFont( font );
	lifes.setFillColor( sf::Color::Green );
	lifes.setString( std::to_string( statsRef.lifes ) );
	sf::Text highscore;
	highscore.setFont( font );
	highscore.setFillColor( sf::Color::Red );
	highscore.setString( std::to_string( statsRef.highscore * 100 ) );

	lifes.setPosition( 600 - lifes.getGlobalBounds().width * 1.1, 0 );
	highscore.setPosition( 300, 0 );

	target.draw( score );
	target.draw( lifes );
	target.draw( highscore );

	return true;
}
