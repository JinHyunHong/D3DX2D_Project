#include "stdafx.h"
#include "InGameScene.h"
#include "Scene/Layer/Layer.h"
#include "Actor.h"
#include "Scene/Component/TransformComponent.h"
#include "Scene/Component/MeshRendererComponent.h"
#include "Scene/Component/AnimatorComponent.h"
#include "Scene/Component/MoveScriptComponent.h"

InGameScene::InGameScene(Tool* const tool) :
	Scene(tool)
{
	auto player_layer = CreateLayer("Player");
	auto player = player_layer->CreateActor();
	player->SetName("Player");
	player->AddComponent<MeshRendererComponent>();
	player->AddComponent<MoveScriptComponent>();
	player->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(2.0f, 2.0f, 1.0f));
	player->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	auto animator = player->AddComponent<AnimatorComponent>();
	animator->AddAnimation("Assets/Animation/Player_Idle_Down.xml");
	animator->AddAnimation("Assets/Animation/Player_Idle_Up.xml");
	animator->AddAnimation("Assets/Animation/Player_Idle_Left.xml");
	animator->AddAnimation("Assets/Animation/Player_Idle_Right.xml");
	animator->SetAnimationMode(AnimationMode::Play);
	animator->SetCurrentAnimation("Idle_Down");
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
