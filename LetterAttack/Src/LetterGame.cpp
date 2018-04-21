/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "LetterGame.hpp"

bool LetterGame::onStart()
{
	return spawn<Letter>( 'A', sf::Vector2f( 0, 0 ), sf::Vector2f( 10, 10 ), 1 );
}

bool LetterGame::onUpdate( float dt )
{
	bool status = true;
	loopEveryGameObject( [&]( auto& go ) {
		if ( !go.onUpdate( dt ) )
			status = false;
	} );

	removeDeadObjects();

	return status;
}

bool LetterGame::onEvent( const sf::Event& event )
{
	bool status = true;
	loopEveryGameObject( [&]( auto& go ) {
		if ( !go.onEvent( event ) )
			status = false;
	} );

	return status;
}

bool LetterGame::onDraw( sf::RenderTarget& target )
{
	bool status = true;
	loopEveryGameObject( [&]( auto& go ) {
		if ( !go.onDraw( target ) )
			status = false;
	} );

	return status;
}

void LetterGame::onEnd()
{}

void LetterGame::removeDeadObjects()
{
	for ( auto it = gameObjects.begin(); it != gameObjects.end(); ) {
		bool wantDie = false;
		std::visit( [&]( Letter& go ) {
			wantDie = go.wantDie();
		}, *it );
		if ( wantDie )
			it = gameObjects.erase( it );
		else
			++it;
	}
}
