/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "Framework.hpp"

namespace con
{
Game::Game( sf::Vector2u&& winSize, const char* winTitle ) :
	window( { winSize.x, winSize.y }, winTitle, sf::Style::Close )
{
	window.setFramerateLimit( 60 );
}

void Game::run()
{
	if ( !onStart() )
		return;

	gameLoop();

	onEnd();
}

void Game::gameLoop()
{
	sf::Clock frameClock;
	float frameDelta = 0;

	while ( true ) {
		if ( !pollEvents() )
			return;

		if ( !onUpdate( frameDelta ) )
			return;

		if ( !draw() )
			return;

		frameDelta = frameClock.restart().asSeconds();
	}
}

bool Game::pollEvents()
{
	sf::Event event;
	while ( window.hasFocus() && window.pollEvent( event ) ) {
		if ( event.type == sf::Event::Closed )
			return false;

		if ( !onEvent( event ) )
			return false;
	}

	return true;
}

bool Game::draw()
{
	window.clear();
	auto status = onDraw( window );
	window.display();

	return status;
}
}
