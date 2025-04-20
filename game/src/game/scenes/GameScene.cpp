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

	for (auto it = m_bullets.begin(); it != m_bullets.end(); ) {
		BulletPawn* bullet = *it;
		bullet->tick(wnd, *this, dt);

		if (!bullet->getIsAlive()) {
			delete bullet;
			it = m_bullets.erase(it);
		}
		else {
			++it;
		}
	}

}

void GameScene::draw(WND wnd)
{
	wnd.setView(m_camera);
	m_player->draw(wnd, *this);

	for (auto& bullet : m_bullets) {
		bullet->draw(wnd, *this);
	}
}

void GameScene::finish()
{
	delete m_player;
	std::cout << "Goodbye!\n";
}

void GameScene::event(WND wnd, const EVENT e)
{
}
