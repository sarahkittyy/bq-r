#include "bq-r.hpp"

#include <iostream>

app::app()
	: m_window(sf::VideoMode(800, 600), "bq-r") {
}

int app::run() {

	while (m_window.isOpen()) {
		// event handling
		sf::Event e;
		while (m_window.pollEvent(e)) {
			switch (e.type) {
			case sf::Event::Closed:
				m_window.close();
				break;
			default:
				break;
			}
		}

		m_window.clear(sf::Color::White);
		// draw here

		m_window.display();
	}

	return 0;
}

int main() {
	app a;
	return a.run();
}
