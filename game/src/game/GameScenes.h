#ifndef GAME_SCENES
#define GAME_SCENES

#include <SFML/Graphics.hpp>
#include "engine/Scene.h"
#include "game/GamePawns.h"

class GameScene : public Scene {
public:
	void begin() override;
	void tick(WND wnd, float dt) override;
	void draw(WND wnd) override;
	void finish() override;
	void event(WND wnd, const EVENT e) override;

private:
	sf::View m_camera;
	PlayerPawn* m_player;
};

#endif // !GAME_SCENES