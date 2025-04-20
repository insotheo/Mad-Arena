#ifndef ENGINE_PAWN
#define ENGINE_PAWN

#include "Scene.h"

class Pawn {
public:
	~Pawn() {}

	virtual void begin() {}
	virtual void tick(WND wnd, SCENE_REF scene, float dt) {}
	virtual void draw(WND wnd, SCENE_REF scene) {}
	virtual void finish() {}
};

#endif // !ENGINE_PAWN