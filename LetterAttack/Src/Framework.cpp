/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "Framework.hpp"

namespace con
{
Game::Game( sf::Vector2u&& winSize, const char* winTitle ) :
	window( {winSize.x, winSize.y}, winTitle, sf::Style::Close )
{
	window.setFramerateLimit( 60 );
}

void Game::run()
{
	if ( onStart() == Exit )
		return;

	gameLoop();

	onEnd();
}

void Game::gameLoop()
{
	sf::Clock frameClock;
	float frameDelta;

	while ( true ) {
		if ( pollEvents() == Exit )
			return;

		if ( onUpdate( frameDelta ) == Exit )
			return;

		if ( draw() == Exit )
			return;

		frameDelta = frameClock.restart().asSeconds();
	}
}

Game::Status Game::pollEvents()
{
	sf::Event event;
	while ( window.hasFocus() && window.pollEvent( event ) ) {
		if ( event.type == sf::Event::Closed )
			return Exit;

		if ( onEvent( event ) == Exit )
			return Exit;
	}
}

Game::Status Game::draw()
{
	window.clear();
	auto status = onDraw( window );
	window.display();

	return status;
}
}
