#include "game/GamePawns.h"

#include <math.h>

sf::Texture PlayerPawn::s_default;
sf::Texture PlayerPawn::s_anim;

void PlayerPawn::begin() {
	if (!s_default.loadFromFile("./assets/player/sprite.png")) { return; }
	if (!s_anim.loadFromFile("./assets/player/animation.png")) { return; }

	m_sprite = new sf::Sprite(s_default);
	m_sprite->setScale({ 2.5f, 2.5f });
	m_sprite->setOrigin(m_sprite->getLocalBounds().getCenter());
}

void PlayerPawn::tick(WND wnd, SCENE_REF scene, float dt)
{
	//movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) m_pos.y -= m_stats.movementSpeed;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) m_pos.y += m_stats.movementSpeed;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) m_pos.x -= m_stats.movementSpeed;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) m_pos.x += m_stats.movementSpeed;

	//rotation
	sf::Vector2f mousePos = wnd.mapPixelToCoords(sf::Mouse::getPosition(wnd), wnd.getView());
	float distance = std::sqrtf(std::powf(m_pos.x - mousePos.x, 2) + std::powf(m_pos.y - mousePos.y, 2));
	float dx = (mousePos.x - m_pos.x) / distance;
	float dy = (mousePos.y - m_pos.y) / distance;
	float angle = std::atan2f(dy, dx);

	m_sprite->setRotation(sf::radians(angle));
	m_sprite->setPosition(m_pos);
}

void PlayerPawn::draw(WND wnd, SCENE_REF scene)
{
	wnd.draw(*m_sprite);
}

void PlayerPawn::finish()
{
	delete m_sprite;
}
