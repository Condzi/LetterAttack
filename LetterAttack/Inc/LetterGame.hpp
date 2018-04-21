/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include <variant>

#include "Framework.hpp"
#include "Letter.hpp"

using GameObjectsVariant = std::variant<Letter>;

struct GameRules final
{
	const sf::Time spawnInterval = sf::seconds( 1 );
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
	sf::Time timeSinceLastSpawn;
	uint16_t score = 0;
	sf::Text scoreText;

	template <typename TLambda>
	void loopEveryGameObject( TLambda&& lambda )
	{
		for ( auto& go : gameObjects )
			std::visit( lambda, go );
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
};