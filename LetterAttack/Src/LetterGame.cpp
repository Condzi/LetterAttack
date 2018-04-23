/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#include "LetterGame.hpp"
#include "Font.hpp"

bool LetterGame::onStart()
{
	bool status = true;
	if ( !spawn<StatsDisplaying>( stats ) )
		status = false;

	timeSinceLastSpawn = rules.spawnInterval;

	if ( !spawnLetter() )
		status = false;

	return status;
}

bool LetterGame::onUpdate( float dt )
{
	bool status = true;
	loopEveryGameObject( [&]( auto& go ) {
		if ( !go.onUpdate( dt ) )
			status = false;
	} );

	checkIfLetterIsOut();

	removeDeadObjects();

	timeSinceLastSpawn -= sf::seconds( dt );
	if ( timeSinceLastSpawn.asSeconds() < 0 ) {
		timeSinceLastSpawn = rules.spawnInterval - timeSinceLastSpawn;
		if ( !spawnLetter() )
			status = false;
		rules.letterVelocity += rules.letterAccelerationToStartVelocity * dt;
	}

	if ( rules.spawnInterval > rules.minSpawnInterval ) {
		rules.spawnInterval -= sf::seconds( rules.decreasingSpawnIntervalVal.asSeconds() * dt );
		if ( rules.spawnInterval < rules.minSpawnInterval )
			rules.spawnInterval = rules.minSpawnInterval;
	}

	if ( stats.lifes <= 0 )
		playAgain();

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
				++stats.score;
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

void LetterGame::checkIfLetterIsOut()
{
	// Passing Letter& letter doesnt work. Hmm.
	loopEveryGameObject( [&]( auto& letter ) {
		using T = std::decay_t<decltype( letter )>;
		if constexpr ( std::is_same_v<T, Letter> )
		{
			if ( auto bounds = letter.getBounds(); bounds.top + bounds.height > 600 ) {
				stats.lifes--;
				letter.kill();
			}
		}
	} );
}

void LetterGame::playAgain()
{
	rules.spawnInterval = rules.startSpawnInterval;
	rules.letterVelocity = 100;
	stats.highscore = stats.score;
	stats.score = 0;
	stats.lifes = 10;

	loopEveryGameObject( [&]( auto& letter ) {
		if ( letter.tag() == "Letter" ) 			{
			stats.score--; // workaround - when this letters will be killd score will be added, so we must 
			// substract it to make it 0 in the end.
			letter.kill();
		}
	} );
}
