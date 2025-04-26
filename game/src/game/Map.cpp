#include "Map.h"

void Map::_begin(const int xSize, const int ySize) {
	if (!m_texture.loadFromFile("./assets/tile.png")) { return; }

	m_sprite = sf::Sprite(m_texture);
	m_sprite.setScale({ 2.25f,2.25f });
	m_sprite.setOrigin(m_sprite.getLocalBounds().size);

	for (int y = 0; y < ySize; ++y) {
		for (int x = 0; x < xSize; ++x) {
			m_tiles.push_back(sf::Vector2f{ m_sprite.getScale().x * x * m_sprite.getLocalBounds().size.x, m_sprite.getScale().y * y * m_sprite.getLocalBounds().size.y});
		}
	}

	m_xBegin = m_tiles.at(0).x - m_sprite.getLocalBounds().size.x - CONFIG_MAP_ADDITIONAL_STEP;
	m_yBegin = m_tiles.at(0).y - m_sprite.getLocalBounds().size.y - CONFIG_MAP_ADDITIONAL_STEP;
	m_xEnd = m_tiles.at(m_tiles.size() - 1).x + CONFIG_MAP_ADDITIONAL_STEP;
	m_yEnd = m_tiles.at(m_tiles.size() - 1).y + CONFIG_MAP_ADDITIONAL_STEP;
}

void Map::_draw(WND wnd, const sf::FloatRect& viewZone)
{
	sf::FloatRect v({viewZone.position.x + m_tiles.at(0).x / 2.f, viewZone.position.y + m_tiles.at(0).y / 2.f }, viewZone.size * 1.5f);
	for (const auto& position : m_tiles) {
		if (v.contains(position)) {
			m_sprite.setPosition(position);
			wnd.draw(m_sprite);
		}
	}
}