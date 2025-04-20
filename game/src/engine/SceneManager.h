#ifndef ENGINE_SCENE_MANAGER
#define ENGINE_SCENE_MANAGER

#include "Core.h"
#include "Scene.h"
#include <vector>

class SceneManager {
public:
	static void push_scene(Scene* scene);
	static void end();

	static void beginScene(const size_t index);

	static void callBegin();
	static void callTick(WND wnd, float dt);
	static void callDraw(WND wnd);
	static void callEvent(WND wnd, const EVENT e);
	static void callFinish();
private:
	static std::vector<Scene*> s_scenes;
	static size_t s_index;
	static bool s_started;
};

#define SWITCH_SCENE(i) SceneManager::beginScene(i)

#endif // !ENGINE_SCENE_MANAGER
