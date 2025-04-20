#ifndef GAME_SCENES
#define GAME_SCENES

#include "engine/Scene.h"

class GameScene : public Scene {
public:
	void begin() override;
	void finish() override;
};

#endif // !GAME_SCENES