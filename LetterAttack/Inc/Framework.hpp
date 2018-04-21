/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <cinttypes>

namespace con
{
class Game
{
public:
	enum Status : bool
	{
		Continue, Exit
	};

	enum LogPriority : uint8_t
	{
		Info, Warning, Error
	};

	Game( sf::Vector2u&& winSize, const char* winTitle );
	virtual ~Game() = default;
	Game( Game&& ) = delete;
	Game( const Game& ) = delete;
	Game& operator=( Game&& ) = delete;
	Game& operator=( const Game& ) = delete;

	virtual Status onStart() {}
	virtual Status onUpdate( float dt ) {}
	virtual Status onEvent( const sf::Event& event ) {}
	virtual Status onDraw( sf::RenderTarget& target ) {}
	virtual void onEnd() {}

	void run();
	template <typename ...TArgs>
	void log( LogPriority priority, TArgs&& ...args )
	{
		auto &logger = std::cout;

		switch ( priority ) {
		case Info: logger << "[INFO] "; break;
		case Warning: logger << "[WARN] "; break;
		case Error: logger << "[ ERR] "; break;
		}

		( logger << ... << args ) << '\n';
	}

private:
	sf::RenderWindow window;

	void gameLoop();
	Status pollEvents();
	Status draw();
};
}