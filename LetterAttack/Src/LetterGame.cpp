/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "LetterGame.hpp"

bool LetterGame::onStart()
{
	timeSinceLastSpawn = rules.spawnInterval;
	return true;
}

bool LetterGame::onUpdate( float dt )
{
	bool status = true;
	loopEveryGameObject( [&]( auto& go ) {
		if ( !go.onUpdate( dt ) )
			status = false;
	} );

	removeDeadObjects();

	timeSinceLastSpawn -= sf::seconds( dt );
	if ( timeSinceLastSpawn.asSeconds() < 0 ) {
		timeSinceLastSpawn = rules.spawnInterval - timeSinceLastSpawn;
		if ( !spawnLetter() )
			status = false;
		rules.letterVelocity += rules.letterAccelerationToStartVelocity * dt;
	}

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
{
	// save score?
}

void LetterGame::removeDeadObjects()
{
	uint16_t combo = 0;
	for ( auto it = gameObjects.begin(); it != gameObjects.end(); ) {
		bool wantDie = false;
		std::visit( [&]( auto& go ) {
			if ( wantDie = go.wantDie(); wantDie && go.tag() == "Letter" ) {
				log( Info, "Score: ", ++score * 100 );
				++combo;
			}
		}, *it );
		if ( wantDie )
			it = gameObjects.erase( it );
		else
			++it;
	}

	if ( combo > 1 )
		log( Info, combo, " combo!" );
}

bool LetterGame::spawnLetter()
{
	auto ch = static_cast<char>( con::Random( static_cast<uint16_t>( 'A' ), static_cast<uint16_t>( 'Z' ) ) );
	sf::Vector2f pos{ static_cast<float>( con::Random( 0, 12 ) * 25 ), rules.startYPos };
	sf::Vector2f vel{ 0, rules.letterVelocity };
	return spawn<Letter>( ch, pos, vel, rules.letterAcceleration );

}
