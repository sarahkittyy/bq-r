#pragma once

#include <SFML/Graphics.hpp>

/**
 * @brief main app class
 */
class app {
public:
	/**
	 * @brief initialize app variables
	 *
	 */
	app();

	/**
	 * @brief equivalent to main
	 *
	 * @return program exit code
	 */
	int run();

private:
	// main app window
	sf::RenderWindow m_window;
};
