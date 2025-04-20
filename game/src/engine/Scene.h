#ifndef ENGINE_SCENE
#define ENGINE_SCENE

#include "Core.h"

class Scene {
public:
	~Scene() {}

	virtual void begin() {}
	virtual void tick(WND wnd, float dt) {}
	virtual void draw(WND wnd) {}
	virtual void event(WND wnd, const EVENT e) {}
	virtual void finish() {}
};

#define NEW_SCENE(CLASS_NAME) new CLASS_NAME()

typedef Scene& SCENE_REF;

#endif // !ENGINE_SCENE