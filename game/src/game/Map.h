#ifndef GAME_MAP
#define GAME_MAP

#include "engine/Pawn.h"
#include "game/GameConfig.h"
#include <vector>

class Map : public Pawn {
public:
	Map() : m_sprite(m_texture)
	{}

	void _begin(const int xSize, const int ySize);
	void _draw(WND wnd, const sf::FloatRect& viewZone);

	inline bool isPointOnMap(const sf::Vector2f& point) {
		return point.x >= m_xBegin && point.y >= m_yBegin && point.x <= m_xEnd && point.y <= m_yEnd;
	}

	inline const sf::Vector2f getMapCenter() const { return sf::Vector2f((float)(m_xBegin + m_xEnd) / 2.f, (float)(m_yBegin + m_yEnd) / 2.f); }

	inline std::vector<sf::Vector2f> getSpawnPoints() const {
		std::vector<sf::Vector2f> points = {
			sf::Vector2f(m_xBegin, m_yBegin), sf::Vector2f(m_xEnd, m_yEnd),
			sf::Vector2f(m_xBegin, m_yEnd), sf::Vector2f(m_xEnd, m_yBegin),
			sf::Vector2f((m_xBegin + m_xEnd) / 2.f, m_yBegin), sf::Vector2f((m_xBegin + m_xEnd) / 2.f, m_yEnd),
			sf::Vector2f(m_xBegin, (m_yBegin + m_yEnd) / 2.f), sf::Vector2f(m_xEnd, (m_yBegin + m_yEnd) / 2.f)
		};
		return points;
	}

private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	std::vector<sf::Vector2f> m_tiles;

	float m_xBegin;
	float m_yBegin;
	float m_xEnd;
	float m_yEnd;
};

#endif // !GAME_MAP
