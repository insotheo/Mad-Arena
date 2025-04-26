#ifndef GAME_MAP
#define GAME_MAP

#include "engine/Pawn.h"
#include <vector>

class Map : public Pawn {
public:
	Map() : m_sprite(m_texture)
	{}

	void _begin(const unsigned int xSize, const unsigned int ySize);
	void _draw(WND wnd, const sf::FloatRect& viewZone);

private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	std::vector<sf::Vector2f> m_tiles;
};

#endif // !GAME_MAP
