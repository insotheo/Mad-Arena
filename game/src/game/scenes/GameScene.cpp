#include "game/GameScenes.h"

#include <iostream>

void GameScene::begin() {
	PlayerPawn::loadAssets();
	BulletPawn::loadAssets();

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

	sf::FloatRect viewRect(m_camera.getCenter() - (m_camera.getSize() / 2.f), m_camera.getSize());

	for (auto& bullet : m_bullets) {
		if (viewRect.contains(bullet->getRectangle().position)) {
			bullet->draw(wnd, *this);
		}
	}
}

void GameScene::finish()
{
	delete m_player;

	BulletPawn::unloadAssets();
}

void GameScene::event(WND wnd, const EVENT e)
{
}
