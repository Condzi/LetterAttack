/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include <variant>

#include "Framework.hpp"
#include "Letter.hpp"

using placeholder_t = char;
using GameObjectsVariant = std::variant<Letter>;

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
};