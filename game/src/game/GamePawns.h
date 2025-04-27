#ifndef GAME_PAWNS
#define GAME_PAWNS

#include <SFML/Graphics.hpp>

#include "engine/Pawn.h"

#include "game/GameConfig.h"

class AmmoPack : public Pawn {
public:
	AmmoPack(const sf::Vector2f& initPos) : m_sprite(s_texture)
	{
		m_sprite.setPosition(initPos);
		m_sprite.setScale({ 1.5f, 1.5f });
		m_sprite.setOrigin(m_sprite.getLocalBounds().getCenter());
	}

	void tick(WND wnd, SCENE_REF scene, float dt) override;
	void draw(WND wnd, SCENE_REF scene) override;

	static void loadAssets();
	static void unloadAssets();

	inline const sf::FloatRect& getRect() const { return m_sprite.getGlobalBounds(); }
	inline bool isAlive() const { return m_isAlive; }
	inline void collect() { m_isAlive = false; }
private:
	float m_lifeTimer = 0.f;
	bool m_isAlive = true;
	sf::Sprite m_sprite;

	static sf::Texture s_texture;
	static bool s_loaded;
};

class BulletPawn : public Pawn {
public:
	BulletPawn(const sf::Vector2f& initPos, const sf::Vector2f& dir) 
		: m_sprite(s_bullet), m_pos(initPos), m_delta(dir * CONFIG_BULLET_SPEED)
	{}

	void begin() override;
	void draw(WND wnd, SCENE_REF scene) override;
	void tick(WND wnd, SCENE_REF scene, float dt) override;

	void end();

	inline bool getIsAlive() const { return m_isAlive; };
	inline void kill() { m_isAlive = false; }
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
};

class PlayerPawn : public Pawn {
public:
	PlayerPawn(const sf::Vector2f& initPos)
		: m_sprite(s_default), m_pos(initPos)
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

	inline bool isAlive() const { return m_health > 0; }
	inline void kick(float damage) { m_health -= damage; }
	inline float getHealth() const { return m_health; }

	inline void reloadAmmo() {
		if (m_ammoPacks > 0) {
			m_ammo = CONFIG_PLAYER_AMMO;
			m_ammoPacks -= 1;
		}
	}
	inline void addAmmoPack() { m_ammoPacks += 1; }

	inline void addKill() { m_killCounter += 1; }
	inline int getKills() const { return m_killCounter; }
private:
	sf::Vector2f m_pos;
	sf::Vector2f m_vel = { 0.f, 0.f };

	sf::Sprite m_sprite;

	//assets
	static sf::Texture s_default;
	static sf::Texture s_anim;
	static bool s_assetsLoaded;

	//shooting
	float m_shootTimer = 0.f;
	bool m_canShoot = true;
	unsigned int m_ammo = CONFIG_PLAYER_AMMO;
	unsigned int m_ammoPacks = CONFIG_PLAYER_AMMO_PACK_INIT;

	//stats

	float m_health = CONFIG_PLAYER_INITIAL_HEALTH;
	unsigned int m_killCounter = 0;
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

	inline bool isAlive() const { return m_health > 0; }
	inline void kick(const float damage) { m_health -= damage; }

	static void loadAssets();
	static void unloadAssets();
private:

	float m_health = CONFIG_ENEMY_INTIAL_HEALTH;

	sf::Sprite m_sprite;
	sf::Vector2f m_pos;

	static bool s_loaded;
	static sf::Texture s_texture;
};

#endif // !GAME_PAWNS
