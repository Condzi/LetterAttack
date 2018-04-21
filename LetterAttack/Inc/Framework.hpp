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

	virtual bool onStart() { return true; }
	virtual bool onUpdate( float dt ) { return true; }
	virtual bool onEvent( const sf::Event& event ) { return true; }
	virtual bool onDraw( sf::RenderTarget& target ) { return true; }
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
	bool pollEvents();
	bool draw();
};
}