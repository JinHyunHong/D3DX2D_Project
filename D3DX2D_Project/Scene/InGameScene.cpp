#include "stdafx.h"
#include "InGameScene.h"
#include "Scene/Layer/Layer.h"
#include "Actor.h"
#include "Scene/Component/TransformComponent.h"
#include "Scene/Component/MeshRendererComponent.h"
#include "Scene/Component/AnimatorComponent.h"
#include "Scene/Component/TileRendererComponent.h"
#include "Scene/Component/MoveScriptComponent.h"
#include "Scene/Component/TextRendererComponent.h"
#include "Scene/Component/ColliderComponent.h"

InGameScene::InGameScene(Tool* const tool) :
	Scene(tool)
{

	// 2200.0f, 2600.0f
	camera->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	auto map_layer = CreateLayer("Map");
	auto map = map_layer->CreateActor();
	map->SetName("Map");
	map->AddComponent<MeshRendererComponent>();
	map->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(1.9f, 1.9f, 1.0f));
	map->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	auto animator = map->AddComponent<AnimatorComponent>();
	animator->AddAnimation("Assets/Xml/Map/World_Map.xml");
	animator->SetCurrentAnimation("World_Map");

	auto player_layer = CreateLayer("Player");
	auto player = player_layer->CreateActor();
	player->SetName("Player");
	player->AddComponent<ColliderComponent>()->SetOffsetScale(D3DXVECTOR3(30.0f, 50.0f, 0.0f));
	player->AddComponent<MeshRendererComponent>();
	player->AddComponent<MoveScriptComponent>();
	player->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(2.0f, 2.0f, 1.0f));
	player->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(225.0f, 225.0f, 0.0f));
	animator = player->AddComponent<AnimatorComponent>();
	animator->AddAnimation("Assets/Xml/Animation/Player_Idle_Down.xml");
	animator->AddAnimation("Assets/Xml/Animation/Player_Idle_Up.xml");
	animator->AddAnimation("Assets/Xml/Animation/Player_Idle_Left.xml");
	animator->AddAnimation("Assets/Xml/Animation/Player_Idle_Right.xml");
	animator->AddAnimation("Assets/Xml/Animation/Player_Run_Down.xml");
	animator->AddAnimation("Assets/Xml/Animation/Player_Run_Up.xml");
	animator->AddAnimation("Assets/Xml/Animation/Player_Run_Left.xml");
	animator->AddAnimation("Assets/Xml/Animation/Player_Run_Right.xml");
	animator->SetAnimationMode(AnimationMode::Play);
	animator->SetCurrentAnimation("Idle_Down");

	auto hud_layer = CreateLayer("HUD");
	hud = hud_layer->CreateActor();
	hud->SetName("HUD");
	hud->AddComponent<MeshRendererComponent>();
	hud->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	hud->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	animator = hud->AddComponent<AnimatorComponent>();
	animator->AddAnimation("Assets/Xml/Animation/HUD.xml");
	animator->SetCurrentAnimation("HUD");

	hud->GetComponent<TransformComponent>()->SetParent(player->GetComponent<TransformComponent>().get());
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
