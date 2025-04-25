#include "game/GamePawns.h"

sf::Texture BulletPawn::s_bullet;
sf::Texture BulletPawn::s_endTexture;
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
		if (!m_isEnd) {
			m_pos += m_delta;
			m_sprite.setPosition(m_pos);
		}
		if (m_timer >= m_lifeTime) {
			if (m_isEnd) {
				m_isAlive = false;
			}
			end();
		}
	}
}

void BulletPawn::end()
{
	m_timer = m_lifeTime - 0.15f;
	m_sprite.setTexture(s_endTexture);
	m_isEnd = true;
}

void BulletPawn::draw(WND wnd, SCENE_REF scene) {
	wnd.draw(m_sprite);
}

void BulletPawn::loadAssets() {
	if (!s_textureLoaded) {
		if (!s_bullet.loadFromFile("./assets/bullet.png") || !s_endTexture.loadFromFile("./assets/bullet_end.png")) { return; }
		else s_textureLoaded = true;
	}
}

void BulletPawn::unloadAssets()
{
	if (s_textureLoaded) {
		s_bullet = {};
		s_endTexture = {};
		s_textureLoaded = false;
	}
}
