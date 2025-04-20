#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "engine/SceneManager.h"
#include "game/GameScenes.h"

int main() {
	GameScene* game_scene = new GameScene(); //0

	SceneManager::push_scene(game_scene);

	sf::Clock game_timer;

	sf::RenderWindow window(sf::VideoMode({ 1280, 720 }), "Mad-Arena");
	window.setVerticalSyncEnabled(true);

	game_timer.restart();
	SWITCH_SCENE(0);
	while (window.isOpen()) {
		while (const auto& event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
			SceneManager::callEvent(window, event);
		}
		SceneManager::callTick(window, game_timer.restart().asSeconds());

		window.clear(sf::Color::White);
		SceneManager::callDraw(window);
		window.display();
	}

	SceneManager::end();
	return 0;
}