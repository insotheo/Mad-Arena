#include "game/GameScenes.h"

#include <iostream>

void GameScene::begin() {
	m_player = new PlayerPawn();

	m_player->begin();
	m_camera.setSize({ 800, 600 });
}

void GameScene::tick(WND wnd, float dt)
{
	m_player->tick(wnd, *this, dt);
	m_camera.setCenter(m_player->getPos());
}

void GameScene::draw(WND wnd)
{
	wnd.setView(m_camera);
	m_player->draw(wnd, *this);
}

void GameScene::finish()
{
	delete m_player;
	std::cout << "Goodbye!\n";
}

void GameScene::event(WND wnd, const EVENT e)
{
}
