#include "game/GamePawns.h"

sf::Texture BulletPawn::s_bullet;
bool BulletPawn::s_textureLoaded = false;

void BulletPawn::begin() {
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

void BulletPawn::loadAssets() {
	if (!s_textureLoaded) {
		if (!s_bullet.loadFromFile("./assets/bullet.png")) { return; }
		else s_textureLoaded = true;
	}
}

void BulletPawn::unloadAssets()
{
	if (s_textureLoaded) {
		s_bullet = {};
		s_textureLoaded = false;
	}
}
