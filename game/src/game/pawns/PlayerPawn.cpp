#include "game/GamePawns.h"

#include "game/GameScenes.h"
#include <math.h>

sf::Texture PlayerPawn::s_default;
sf::Texture PlayerPawn::s_anim;

bool PlayerPawn::s_assetsLoaded = false;

void PlayerPawn::begin() {
	m_sprite.setScale({ 2.5f, 2.5f });
	m_sprite.setOrigin(m_sprite.getLocalBounds().getCenter());
}

void PlayerPawn::tick(WND wnd, SCENE_REF scene, float dt)
{
	m_sprite.setTexture(s_default);
	//movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) m_vel.y -= CONFIG_PLAYER_MOVEMENT_SPEED;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) m_vel.y += CONFIG_PLAYER_MOVEMENT_SPEED;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) m_vel.x -= CONFIG_PLAYER_MOVEMENT_SPEED;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) m_vel.x += CONFIG_PLAYER_MOVEMENT_SPEED;

	//rotation
	sf::Vector2f mousePos = wnd.mapPixelToCoords(sf::Mouse::getPosition(wnd), wnd.getView());
	float distance = std::sqrtf(std::powf(m_pos.x - mousePos.x, 2) + std::powf(m_pos.y - mousePos.y, 2));
	float dx = (mousePos.x - m_pos.x) / distance;
	float dy = (mousePos.y - m_pos.y) / distance;
	float angle = std::atan2f(dy, dx);

	//shooting
	if (!m_canShoot) {
		m_shootTimer += dt;
		if (m_shootTimer >= CONFIG_PLAYER_SHOOT_DELAY) {
			m_shootTimer = 0.f;
			m_canShoot = true;
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && m_canShoot && m_ammo > 0) {
		m_sprite.setTexture(s_anim);
		sf::Vector2f dir(dx, dy);

		BulletPawn* bullet = new BulletPawn(m_pos + sf::Vector2f{1.5f * m_sprite.getLocalBounds().size.x * dir.x, 1.5f * m_sprite.getLocalBounds().size.y * dir.y},
			dir);
		bullet->begin();
		static_cast<GameScene&>(scene).push_bullet(bullet);
		m_ammo -= 1;

		m_vel -= dir * CONFIG_PLAYER_KICKBACK;

		m_canShoot = false;
	}

	m_pos += m_vel;

	m_sprite.setRotation(sf::radians(angle));
	m_sprite.setPosition(m_pos);

	m_vel = { 0, 0 };
}

void PlayerPawn::draw(WND wnd, SCENE_REF scene)
{
	wnd.draw(m_sprite);
}

void PlayerPawn::finish()
{
	PlayerPawn::unloadAssets();
}

void PlayerPawn::loadAssets()
{
	if (!s_assetsLoaded) {
		if (!s_default.loadFromFile("./assets/player/sprite.png")) { return; }
		if (!s_anim.loadFromFile("./assets/player/shooting.png")) { return; }

		s_assetsLoaded = true;
	}
}

void PlayerPawn::unloadAssets()
{
	if (s_assetsLoaded) {
		s_default = {};
		s_anim = {};

		s_assetsLoaded = false;
	}
}
