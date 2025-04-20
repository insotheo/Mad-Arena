#include <SFML/Graphics.hpp>

int main() {
	sf::RenderWindow window(sf::VideoMode({ 400, 400 }), "Hello, World!");
	window.setVerticalSyncEnabled(true);

	while (window.isOpen()) {
		while (const auto& event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
		}
		window.clear(sf::Color::White);

		window.display();
	}

	return 0;
}