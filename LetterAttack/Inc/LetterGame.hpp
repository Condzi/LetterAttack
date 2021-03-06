/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include <variant>

#include "Framework.hpp"
#include "StatsDisplaying.hpp"
#include "Letter.hpp"

using GameObjectsVariant = std::variant<Letter, StatsDisplaying>;

struct GameRules final
{
	const sf::Time startSpawnInterval = sf::seconds( 1 );
	sf::Time spawnInterval = startSpawnInterval;
	const sf::Time minSpawnInterval = sf::seconds( 0.4f );
	const sf::Time decreasingSpawnIntervalVal = sf::seconds( 0.01f );
	float letterVelocity = 100;
	const float letterAcceleration = 150;
	const float letterAccelerationToStartVelocity = 100;
	const float startYPos = 100;
};

// TODO: Display time left to spawn, make lifes.
class LetterGame final :
	public con::Game
{
public:
	using con::Game::Game;

	bool onStart() override;
	bool onUpdate( float dt ) override;
	bool onEvent( const sf::Event& event ) override;
	bool onDraw( sf::RenderTarget& target ) override;
	void onEnd() override;

private:
	std::vector<GameObjectsVariant> gameObjects;
	GameRules rules;
	PlayerStats stats;
	sf::Time timeSinceLastSpawn;

	template <typename TLambda>
	void loopEveryGameObject( TLambda&& lambda )
	{
		for ( auto& go : gameObjects )
			std::visit( std::forward<TLambda>( lambda ), go );
	}

	template <typename TGameObject, typename ...TArgs>
	bool spawn( TArgs&& ...args )
	{
		auto& variant = gameObjects.emplace_back( TGameObject( std::forward<TArgs>( args )... ) );

		bool status = true;
		std::visit( [&]( auto& go ) {
			status = go.onSpawn();
		}, variant );

		return status;
	}

	void removeDeadObjects();
	bool spawnLetter();
	void checkIfLetterIsOut();
	void playAgain();
};