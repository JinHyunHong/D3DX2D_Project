#include "stdafx.h"
#include "SceneManager.h"
#include "Scene/Scene.h"


SceneManager::SceneManager(class Tool* const tool) :
	ISubsystem(tool)
{
}

SceneManager::~SceneManager()
{
	scenes.clear();
}

bool SceneManager::Initialize()
{
	CreateScene("Game");
	SetCurrentScene("Game");

	return true;
}

void SceneManager::Update()
{
	if (!current_scene.expired())
		current_scene.lock()->Update();
}

void SceneManager::Destroy()
{
}

auto SceneManager::GetCurrentScene_Raw() -> class Scene* const
{
	return current_scene.expired() ? nullptr : current_scene.lock().get();
}

auto SceneManager::GetCurrentScene() const -> std::shared_ptr<class Scene>
{
	return current_scene.expired() ? nullptr : current_scene.lock();
}

void SceneManager::SetCurrentScene(const std::string& scene_name)
{
	if (scenes.find(scene_name) == scenes.end())
	{
		assert(false);
		return;
	}

	current_scene = scenes[scene_name];
}

auto SceneManager::CreateScene(const std::string& scene_name) -> std::shared_ptr<class Scene>
{
	if (scenes.find(scene_name) != scenes.end())
	{
		assert(false);
		return nullptr;
	}

	auto new_scene = std::make_shared<Scene>(tool);

	scenes[scene_name] = new_scene;

	return new_scene;
}
