#include "game/GameScenes.h"

#include <iostream>

void GameScene::begin() {
	m_player = new PlayerPawn();

	m_player->begin();
}

void GameScene::tick(WND wnd, float dt)
{
	m_player->tick(*this, dt);
}

void GameScene::draw(WND wnd)
{
	wnd.clear(sf::Color::Blue);
	m_player->draw(wnd, *this);
}

void GameScene::finish()
{
	std::cout << "Goodbye!\n";
}

void GameScene::event(WND wnd, const EVENT e)
{
}
