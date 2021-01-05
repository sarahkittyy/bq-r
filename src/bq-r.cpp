#include "bq-r.hpp"

#include <iostream>

#include <imgui.h>
#include <imgui-SFML.h>

app::app()
	: m_window(sf::VideoMode(800, 600), "bq-r") {
	ImGui::SFML::Init(m_window);
}

int app::run() {
	// clock for measuring deltas between frames
	sf::Clock imgui_clock;
	while (m_window.isOpen()) {
		// event handling
		sf::Event e;
		while (m_window.pollEvent(e)) {
			ImGui::SFML::ProcessEvent(e);
			switch (e.type) {
			case sf::Event::Closed:
				m_window.close();
				break;
			default:
				break;
			}
		}

		ImGui::SFML::Update(m_window, imgui_clock.restart());
		// render imgui here
		ImGui::Begin("nya");
		ImGui::Button("test");
		ImGui::End();

		ImGui::EndFrame();

		m_window.clear(sf::Color::White);
		// draw here

		ImGui::SFML::Render(m_window);
		m_window.display();
	}

	return 0;
}

int main() {
	app a;
	return a.run();
}
