#include "game/GameScenes.h"

#include <iostream>

#define ENEMY_SPAWN 2 //in seconds

void GameScene::begin() {
	EnemyPawn::loadAssets();
	BulletPawn::loadAssets();
	PlayerPawn::loadAssets();

	m_map = new Map();
	m_player = new PlayerPawn();

	m_map->_begin(50, 50);
	m_player->begin();
	m_camera.setSize({ 800, 600 });
}

void GameScene::tick(WND wnd, float dt)
{
	m_player->tick(wnd, *this, dt);
	m_camera.setCenter(m_player->getPos());

	m_enemySpawnerTimer += dt;
	if (m_enemySpawnerTimer >= ENEMY_SPAWN) {
		m_enemySpawnerTimer = 0.f;

		EnemyPawn* enemy = new EnemyPawn();
		enemy->_begin({ 0, 0 });
		m_enemies.push_back(enemy);
	}

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

	for (auto it = m_enemies.begin(); it != m_enemies.end(); ) {
		EnemyPawn* enemy = *it;
		enemy->ai_tick(wnd, *m_player, dt);

		++it;
	}
}

void GameScene::draw(WND wnd)
{
	wnd.setView(m_camera);
	wnd.clear(sf::Color{ 8, 118, 119, 255 });
	sf::FloatRect viewRect(m_camera.getCenter() - (m_camera.getSize() / 2.f), m_camera.getSize());

	m_map->_draw(wnd, viewRect);

	m_player->draw(wnd, *this);

	for (auto& enemy : m_enemies) {
		if (viewRect.findIntersection({enemy->getPos(), enemy->getRect().size * 1.25f})) {
			enemy->draw(wnd, *this);
		}
	}

	for (auto& bullet : m_bullets) {
		if (viewRect.contains(bullet->getRectangle().position)) {
			bullet->draw(wnd, *this);
		}
	}
}

void GameScene::finish()
{
	if (m_bullets.size() > 0) {
		for (auto it = m_bullets.begin(); it != m_bullets.end(); ) {
			BulletPawn* bullet = *it;
			delete bullet;
			it = m_bullets.erase(it);
		}
	}

	if (m_enemies.size() > 0) {
		for (auto it = m_enemies.begin(); it != m_enemies.end(); ) {
			EnemyPawn* enemy = *it;
			delete enemy;
			it = m_enemies.erase(it);
		}
	}

	delete m_player;
	delete m_map;

	BulletPawn::unloadAssets();
	EnemyPawn::unloadAssets();
}

void GameScene::event(WND wnd, const EVENT e)
{
}
