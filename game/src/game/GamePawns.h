#ifndef GAME_PAWNS
#define GAME_PAWNS

#include <SFML/Graphics.hpp>

#include "engine/Pawn.h"

struct PlayerStats {
	float movementSpeed;
};

class PlayerPawn : public Pawn {
public:
	~PlayerPawn() { finish(); }

	void begin() override;
	void tick(WND wnd, SCENE_REF scene, float dt) override;
	void draw(WND wnd, SCENE_REF scene) override;
	void finish() override;

	inline const sf::Vector2f& getPos() const { return m_pos; };
	inline const PlayerStats& getStats() const { return m_stats; };
private:
	sf::Vector2f m_pos = {0.f, 0.f};

	sf::Sprite* m_sprite;

	static sf::Texture s_default;
	static sf::Texture s_anim;

	//STATS
	PlayerStats m_stats = {2.f};
};

#endif // !GAME_PAWNS
