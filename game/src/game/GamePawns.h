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

	void end();

	inline bool getIsAlive() const { return m_isAlive; };
	inline const sf::FloatRect& getRectangle() const { return m_sprite.getGlobalBounds(); };

	static void loadAssets();
	static void unloadAssets();
private:
	sf::Sprite m_sprite;

	static sf::Texture s_bullet;
	static sf::Texture s_endTexture;
	static bool s_textureLoaded;

	float m_timer = 0;
	bool m_isAlive = true;
	bool m_isEnd = false;

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
	inline const sf::FloatRect& getRect() const { return m_sprite.getGlobalBounds(); }
	inline const PlayerStats& getStats() const { return m_stats; };
private:
	sf::Vector2f m_pos = {0.f, 0.f};
	sf::Vector2f m_vel = { 0.f, 0.f };

	sf::Sprite m_sprite;

	//assets
	static sf::Texture s_default;
	static sf::Texture s_anim;
	static bool s_assetsLoaded;

	//shooting
	float m_shootTimer = 0.f;
	bool m_canShoot = true;

	//STATS
	PlayerStats m_stats;
};

class EnemyPawn : public Pawn {
public:
	EnemyPawn()
		: m_sprite(s_texture)
	{}
	
	void _begin(const sf::Vector2f& initPos);
	void ai_tick(WND wnd, const PlayerPawn& player, float dt);
	void draw(WND wnd, SCENE_REF scene) override;

	inline const sf::FloatRect& getRect() const { return m_sprite.getGlobalBounds(); }
	inline const sf::Vector2f& getPos() const { return m_pos; }

	static void loadAssets();
	static void unloadAssets();
private:

	const float m_speed = 2.f;

	sf::Sprite m_sprite;
	sf::Vector2f m_pos;

	static bool s_loaded;
	static sf::Texture s_texture;
};

#endif // !GAME_PAWNS
