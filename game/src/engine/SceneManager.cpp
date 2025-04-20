#include "SceneManager.h"

std::vector<Scene*> SceneManager::s_scenes;
size_t SceneManager::s_index;
bool SceneManager::s_started = false;

void SceneManager::push_scene(Scene* scene)
{
	s_scenes.push_back(scene);
}

void SceneManager::end()
{
	for (Scene* scene_p : s_scenes) {
		delete scene_p;
	}
}

void SceneManager::beginScene(const size_t index)
{
	if (index > s_scenes.size()) {
		return;
	}
	if (s_started) {
		callFinish();
	}
	s_index = index;
	s_started = true;
	callBegin();
}

void SceneManager::callBegin()
{
	if (s_started) {
		s_scenes.at(s_index)->begin();
	}
}

void SceneManager::callTick(WND wnd, float dt)
{
	if (s_started) {
		s_scenes.at(s_index)->tick(wnd, dt);
	}
}

void SceneManager::callDraw(WND wnd)
{
	if (s_started) {
		s_scenes.at(s_index)->draw(wnd);
	}
}

void SceneManager::callEvent(WND wnd, EVENT e)
{
	if (s_started) {
		s_scenes.at(s_index)->event(wnd, e);
	}
}

void SceneManager::callFinish()
{
	s_scenes.at(s_index)->finish();
}
