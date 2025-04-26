#ifndef GAME_SCENES
#define GAME_SCENES

#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include "game/GameConfig.h"
#include "engine/Scene.h"
#include "game/GamePawns.h"
#include "game/Map.h"

class GameScene : public Scene {
public:
	void begin() override;
	void tick(WND wnd, float dt) override;
	void draw(WND wnd) override;
	void finish() override;
	void event(WND wnd, const EVENT e) override;

	inline void push_bullet(BulletPawn* bullet) { m_bullets.push_back(bullet); };
private:
	std::mt19937 m_randEng;
	std::uniform_int_distribution<int> m_dist;

	sf::View m_camera;
	PlayerPawn* m_player;
	Map* m_map;

	std::vector<BulletPawn*> m_bullets;
	std::vector<EnemyPawn*> m_enemies;

	float m_enemySpawnerTimer = 0.f;
	std::vector<sf::Vector2f> m_spawnersPoints; //array: 8 points
};

#endif // !GAME_SCENES