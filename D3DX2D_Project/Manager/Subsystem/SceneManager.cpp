#include "stdafx.h"
#include "SceneManager.h"
#include "Scene/Scene.h"
#include "Scene/MenuScene.h"
#include "Scene/NameSelectScene.h"
#include "Scene/InGameScene.h"
#include "Scene/MapEditorScene.h"


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
	CreateScene<MenuScene>("Menu");
	CreateScene<NameSelectScene>("NameSelect");
	CreateScene<MapEditorScene>("MapEditor");
	CreateScene<InGameScene>("InGame");

	SetCurrentScene("Menu");

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
	assert(scenes.find(scene_name) != scenes.end());
	
	if(!current_scene.expired())
		current_scene.lock().get()->Destroy();

	current_scene = scenes[scene_name];
	current_scene.lock().get()->Initialize();
}