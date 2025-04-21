#ifndef GAME_PAWNS
#define GAME_PAWNS

#include <SFML/Graphics.hpp>

#include "engine/Pawn.h"

struct PlayerStats {
	float movementSpeed;

	float bulletSpeed;
	float bulletLifeTime; //in SECONDS
	float kickback;
	float shootDelay; //in SECONDS
};

class BulletPawn : public Pawn {
public:
	BulletPawn(const sf::Vector2f& initPos, const sf::Vector2f& dir, const float lifeTime) 
		: m_sprite(s_bullet), m_pos(initPos), m_delta(dir), m_lifeTime(lifeTime)
	{}

	void begin() override;
	void draw(WND wnd, SCENE_REF scene) override;
	void tick(WND wnd, SCENE_REF scene, float dt) override;

	inline bool getIsAlive() const { return m_isAlive; };
	inline const sf::FloatRect& getRectangle() const { return m_sprite.getGlobalBounds(); };

	static void loadAssets();
	static void unloadAssets();
private:
	sf::Sprite m_sprite;

	static sf::Texture s_bullet;
	static bool s_textureLoaded;

	float m_timer = 0;
	bool m_isAlive = true;

	sf::Vector2f m_pos;

	//PARAMS
	const sf::Vector2f m_delta;
	const float m_lifeTime;
};

class PlayerPawn : public Pawn {
public:
	PlayerPawn()
		: m_sprite(s_default)
	{ }
	~PlayerPawn() { finish(); }

	void begin() override;
	void tick(WND wnd, SCENE_REF scene, float dt) override;
	void draw(WND wnd, SCENE_REF scene) override;
	void finish() override;

	static void loadAssets();
	static void unloadAssets();

	inline const sf::Vector2f& getPos() const { return m_pos; };
	inline const PlayerStats& getStats() const { return m_stats; };
private:
	sf::Vector2f m_pos = {0.f, 0.f};

	sf::Sprite m_sprite;

	//assets
	static sf::Texture s_default;
	static sf::Texture s_anim;
	static bool s_assetsLoaded;

	//shooting
	float m_shootTimer = 0.f;
	bool m_canShoot = true;

	//STATS
	PlayerStats m_stats = {2.f, 1.f, 1.5f, 10.f, 0.07f};
};

#endif // !GAME_PAWNS
