#include "game/GamePawns.h"

sf::Texture BulletPawn::s_bullet;

void BulletPawn::begin() {
	if (!s_bullet.loadFromFile("./assets/bullet.png")) { return; }

	m_sprite = sf::Sprite(s_bullet);
	m_sprite.setOrigin(m_sprite.getLocalBounds().getCenter());
	m_sprite.setScale({ 2, 2 });
	m_sprite.setPosition(m_pos);
}

void BulletPawn::tick(WND wnd, SCENE_REF scene, float dt)
{
	if (m_isAlive) {
		m_timer += dt;
		m_pos += m_delta;
		m_sprite.setPosition(m_pos);
		if (m_timer >= m_lifeTime) {
			m_isAlive = false;
		}
	}
}

void BulletPawn::draw(WND wnd, SCENE_REF scene) {
	wnd.draw(m_sprite);
}