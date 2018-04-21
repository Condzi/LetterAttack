/*
	Conrad 'Condzi' Kubacki 2018
	https://github.com/condzi
*/

#pragma once

#include <iostream>
#include <random>
#include <chrono>
#include <cinttypes>

#include <SFML/Graphics.hpp>

namespace con
{

namespace priv
{
inline static std::mt19937
rng( static_cast<uint32_t>( std::chrono::steady_clock::now().time_since_epoch().count() ) );
}

template <typename T, typename Y>
T Random( const T& min, const Y& max )
{
	static_assert( std::is_integral_v<T> || std::is_floating_point_v<T> );
	T maxCasted = static_cast<T>( max );

	if ( min > maxCasted )
		throw std::range_error( "min > max" );

	if constexpr ( std::is_integral_v<T> )
	{
		std::uniform_int_distribution<T> dist( min, maxCasted );
		return dist( priv::rng );
	} else if constexpr ( std::is_floating_point_v<T> )
	{
		std::uniform_real_distribution<T> dist( min, maxCasted );
		return dist( priv::rng );
	}
}

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