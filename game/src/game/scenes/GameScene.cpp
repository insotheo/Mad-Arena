#include "game/GameScenes.h"

#include <iostream>

void GameScene::begin() {
	m_isPaused = false;
	m_isGameOver = false;
	std::random_device rd;
	m_randEng = std::mt19937(rd());
	m_dist = std::uniform_int_distribution<int>(0, 7);

	EnemyPawn::loadAssets();
	BulletPawn::loadAssets();
	AmmoPack::loadAssets();
	PlayerPawn::loadAssets();

	m_map = new Map();
	m_map->_begin(CONFIG_GAME_MAP_SIZE_X, CONFIG_GAME_MAP_SIZE_Y);
	m_spawnersPoints = m_map->getSpawnPoints();

	m_packsDistX = std::uniform_real_distribution<float>(m_spawnersPoints[0].x, m_spawnersPoints[1].x);
	m_packsDistY = std::uniform_real_distribution<float>(m_spawnersPoints[0].y, m_spawnersPoints[1].y);

	m_player = new PlayerPawn(m_map->getMapCenter());

	m_player->begin();
	m_camera.setSize({ 800, 600 });
}

void GameScene::tick(WND wnd, float dt)
{
	if (m_isPaused) {
		return;
	}

	if (m_isGameOver) {
		return;
	}

	m_player->tick(wnd, *this, dt);
	m_camera.setCenter(m_player->getPos());

	m_enemySpawnerTimer += dt;
	if (m_enemySpawnerTimer >= CONFIG_ENEMY_SPAWN_DELAY) {
		m_enemySpawnerTimer = 0.f;

		EnemyPawn* enemy = new EnemyPawn();
		int index = m_dist(m_randEng);
		enemy->_begin(m_spawnersPoints.at(index));
		m_enemies.push_back(enemy);
	}

	m_packSpawnerTimer += dt;
	if (m_packSpawnerTimer >= CONFIG_AMMO_PACK_SPAWN_DELAY) {
		m_packSpawnerTimer = 0.f;

		float x = m_packsDistX(m_randEng);
		float y = m_packsDistY(m_randEng);

		AmmoPack* pack = new AmmoPack({ x, y });
		m_ammoPacks.push_back(pack);
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
			m_player->addKill();
			delete enemy;
			it = m_enemies.erase(it);
		}
		else {
			++it;
		}
	}

	for (auto it = m_ammoPacks.begin(); it != m_ammoPacks.end(); ) {
		AmmoPack* pack = *it;
		pack->tick(wnd, *this, dt);

		if (!pack->isAlive()) {
			delete pack;
			it = m_ammoPacks.erase(it);
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

	//player coollect ammo pack
	for (auto& pack : m_ammoPacks) {
		if (pack->isAlive()) {
			sf::FloatRect playerRect(m_player->getPos() - m_player->getRect().size / 2.f, { m_player->getRect().size / 2.f });
			if (playerRect.contains(pack->getRect().position)) {
				m_player->addAmmoPack();
				pack->collect();
				continue;
			}
		}
	}

	if (m_player->getHealth() <= 0) {
		m_isGameOver = true;
		m_isPaused = false;
	}
}

void GameScene::draw(WND wnd)
{
	wnd.setView(m_camera);
	if (m_isGameOver) {
		wnd.clear(sf::Color::Black);
		m_player->draw(wnd, *this);
		return;
	}
	wnd.clear(sf::Color{ 8, 118, 119, 255 });
	sf::FloatRect viewRect(m_camera.getCenter() - (m_camera.getSize() / 2.f), m_camera.getSize());

	m_map->_draw(wnd, viewRect);

	if (!m_isPaused) {
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

		for (auto& pack : m_ammoPacks) {
			if (viewRect.contains(pack->getRect().position)) {
				pack->draw(wnd, *this);
			}
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

	if (m_ammoPacks.size() > 0) {
		for (auto it = m_ammoPacks.begin(); it != m_ammoPacks.end(); ) {
			AmmoPack* pack = *it;
			delete pack;
			it = m_ammoPacks.erase(it);
		}
	}

	delete m_player;
	delete m_map;

	BulletPawn::unloadAssets();
	EnemyPawn::unloadAssets();
	AmmoPack::unloadAssets();
}

void GameScene::event(WND wnd, const EVENT e)
{
	//player reload
	if (const auto* releasedKey = e->getIf<sf::Event::KeyReleased>()) {
		if (releasedKey->code == sf::Keyboard::Key::R) {
			m_player->reloadAmmo();
		}
		else if (releasedKey->code == sf::Keyboard::Key::Escape && !m_isGameOver) {
			m_isPaused = !m_isPaused;
		}
	}

	if (e->is<sf::Event::FocusLost>() && !m_isGameOver) {
		m_isPaused = true;
	}
}
