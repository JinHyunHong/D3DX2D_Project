#include "stdafx.h"
#include "InGameScene.h"
#include "Scene/Layer/Layer.h"
#include "Actor.h"
#include "Scene/Component/TransformComponent.h"
#include "Scene/Component/MeshRendererComponent.h"
#include "Scene/Component/AnimatorComponent.h"
#include "Scene/Component/TileRendererComponent.h"
#include "Scene/Component/MoveScriptComponent.h"

InGameScene::InGameScene(Tool* const tool) :
	Scene(tool)
{
	auto map_layer = CreateLayer("Map");
	auto map = map_layer->CreateActor();
	map->SetName("Map");
	map->AddComponent<MeshRendererComponent>();
	map->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(1.5f, 1.5f, 1.0f));
	map->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(.0f, 0.0f, 0.0f));
	auto animator = map->AddComponent<AnimatorComponent>();
	animator->AddAnimation("Assets/Xml/Map/World_Map.xml");
	animator->SetCurrentAnimation("World_Map");


	auto base_map = CreateLayer("BaseMap");
	auto tile1 = base_map->CreateActor();
	tile1->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(2.0f, 2.0f, 1.0f));
	tile1->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	tile1->AddComponent<TileRendererComponent>()->AddTile("Assets/Xml/Map/Base_Map.xml", 0);

	auto player_layer = CreateLayer("Player");
	auto player = player_layer->CreateActor();
	player->SetName("Player");
	player->AddComponent<MeshRendererComponent>();
	player->AddComponent<MoveScriptComponent>();
	player->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(2.0f, 2.2f, 1.0f));
	player->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(250.0f, 250.0f, 0.0f));
	animator = player->AddComponent<AnimatorComponent>();
	animator->AddAnimation("Assets/Xml/Animation/Player_Idle_Down.xml");
	animator->AddAnimation("Assets/Xml/Animation/Player_Idle_Up.xml");
	animator->AddAnimation("Assets/Xml/Animation/Player_Idle_Left.xml");
	animator->AddAnimation("Assets/Xml/Animation/Player_Idle_Right.xml");
	animator->SetAnimationMode(AnimationMode::Play);
	animator->SetCurrentAnimation("Idle_Down");

	camera->GetComponent<TransformComponent>()->SetParent(player->GetComponent<TransformComponent>().get());
}

InGameScene::~InGameScene()
{
}

void InGameScene::Initialize()
{
	Scene::Initialize();
}

void InGameScene::Input()
{
}

void InGameScene::Update()
{
	Input();
	Scene::Update();
}

void InGameScene::Destroy()
{
	Scene::Destroy();
}
