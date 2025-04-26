#include "game/GameScenes.h"

#include <iostream>

void GameScene::begin() {
	std::random_device rd;
	m_randEng = std::mt19937(rd());
	m_dist = std::uniform_int_distribution<int>(0, 7);

	EnemyPawn::loadAssets();
	BulletPawn::loadAssets();
	PlayerPawn::loadAssets();

	m_map = new Map();
	m_map->_begin(CONFIG_GAME_MAP_SIZE_X, CONFIG_GAME_MAP_SIZE_Y);
	m_spawnersPoints = m_map->getSpawnPoints();

	m_player = new PlayerPawn(m_map->getMapCenter());

	m_player->begin();
	m_camera.setSize({ 800, 600 });
}

void GameScene::tick(WND wnd, float dt)
{
	m_player->tick(wnd, *this, dt);
	m_camera.setCenter(m_player->getPos());

	m_enemySpawnerTimer += dt;
	if (m_enemySpawnerTimer >= CONFIG_ENEMY_SPAWN_DELAY) {
		m_enemySpawnerTimer = 0.f;

		EnemyPawn* enemy = new EnemyPawn();
		int index = m_dist(m_randEng);;
		enemy->_begin(m_spawnersPoints.at(index));
		m_enemies.push_back(enemy);
	}

	//updates
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

		if (!enemy->isAlive()) {
			delete enemy;
			it = m_enemies.erase(it);
		}
		else {
			++it;
		}
	}

	//bullet intersections
	for (auto& bullet : m_bullets) {
		if (bullet->getIsAlive()) {
			for (auto& enemy : m_enemies) {
				sf::FloatRect enemyRect(enemy->getPos() - (enemy->getRect().size / 4.f), enemy->getRect().size / 2.f);
				if (enemyRect.contains(bullet->getRectangle().position)) {
					bullet->kill();
					enemy->kick(CONFIG_BULLET_DAMAGE);
					break;
				}
			}
		}
	}

	//player being attacked
	for (auto& enemy : m_enemies) {
		if (enemy->isAlive()) {
			sf::FloatRect enemyRect(enemy->getPos() - (enemy->getRect().size / 8.f), enemy->getRect().size / 4.f);
			if (enemyRect.findIntersection({m_player->getPos() - (m_player->getRect().size / 2.f), m_player->getRect().size })) {
				m_player->kick(CONFIG_ENEMY_DAMAGE);
				continue;
			}
		}
	}

	if (!m_map->isPointOnMap(m_player->getPos())) {
		m_player->kick(CONFIG_GAME_WATER_DAMAGE);
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
		if (viewRect.findIntersection({ enemy->getPos() - (enemy->getRect().size / 2.f), enemy->getRect().size * 2.f })) {
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
