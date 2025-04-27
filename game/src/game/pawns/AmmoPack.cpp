#include "game/GamePawns.h"

sf::Texture AmmoPack::s_texture;
bool AmmoPack::s_loaded = false;

void AmmoPack::tick(WND wnd, SCENE_REF scene, float dt)
{
	if (m_isAlive) {
		m_lifeTimer += dt;
		if (m_lifeTimer >= CONFIG_AMMO_PACK_LIFETIME) {
			m_isAlive = false;
		}
	}
}

void AmmoPack::draw(WND wnd, SCENE_REF scene)
{
	wnd.draw(m_sprite);
}

void AmmoPack::loadAssets() {
	if (!s_loaded) {
		if (!s_texture.loadFromFile("./assets/ammo_pack.png")) { return; }
		s_loaded = true;
	}
}

void AmmoPack::unloadAssets(){
	if (s_loaded) {
		s_texture = {};
		s_loaded = false;
	}
}