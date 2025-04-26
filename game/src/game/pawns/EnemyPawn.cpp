#include "game/GamePawns.h"

#include <cmath>

sf::Texture EnemyPawn::s_texture;
bool EnemyPawn::s_loaded = false;

void EnemyPawn::_begin(const sf::Vector2f& initPos)
{
	m_pos = { initPos };
	m_sprite.setPosition(m_pos);
	m_sprite.setScale(sf::Vector2f{ 2.7f, 2.7f });
	m_sprite.setOrigin(m_sprite.getLocalBounds().getCenter());
}

void EnemyPawn::ai_tick(WND wnd, const PlayerPawn& player, float dt)
{
	const sf::Vector2f plrPos = player.getPos();

	float dx = plrPos.x - m_pos.x;
	float dy = plrPos.y - m_pos.y;
	float dist = std::sqrtf(std::powf(dx, 2) + std::powf(dy, 2));
	
	if (dist > 0) {
		sf::Vector2f dir(dx / dist, dy / dist);
		float angle = std::atan2f(dir.y, dir.x);

		m_pos += dir * CONFIG_ENEMY_SPEED;

		m_sprite.setRotation(sf::radians(angle));
		m_sprite.setPosition(m_pos);
	}
}

void EnemyPawn::draw(WND wnd, SCENE_REF scene)
{
	wnd.draw(m_sprite);
}

void EnemyPawn::loadAssets() {
	if (!s_loaded) {
		if (!s_texture.loadFromFile("./assets/enemy.png")) { return; }
		s_loaded = true;
	}
}

void EnemyPawn::unloadAssets() {
	if (s_loaded) {
		s_texture = {};
		s_loaded = false;
	}
}