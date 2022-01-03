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

	LoadFromFile("Assets/Xml/Map/New_Map.xml", "World_Map", true);

	auto player_layer = CreateLayer("Player");
	player = player_layer->CreateActor();
	player->SetName("Player");
	player->AddComponent<ColliderComponent>()->SetOffsetScale(D3DXVECTOR3(30.0f, 50.0f, 0.0f));
	player->AddComponent<MeshRendererComponent>();
	player->AddComponent<MoveScriptComponent>();
	player->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(2.0f, 2.0f, 1.0f));
	player->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(225.0f, 225.0f, 0.0f));
	auto animator = player->AddComponent<AnimatorComponent>();
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
	auto transform = player->GetComponent<TransformComponent>();
	auto position = transform->GetPosition();
	auto tile_actor = tile_layer->GetActor(GetTileIndex(D3DXVECTOR2(position.x, position.y)));
	auto tile_transform = tile_actor->GetComponent<TransformComponent>();
	if (!tile_actor->GetComponent<TileRendererComponent>()->GetTile()->IsMove())
	{
		if (auto move_component = player->GetComponent<MoveScriptComponent>())
		{
			switch (move_component->GetDirection())
			{
			case Direction::Up:
			{
				transform->SetPosition(D3DXVECTOR3(position.x, position.y + 1, position.z));
				break;
			}
			case Direction::Right:
			{
				transform->SetPosition(D3DXVECTOR3(position.x - 1, position.y, position.z));
				break;
			}
			case Direction::Down:
			{
				transform->SetPosition(D3DXVECTOR3(position.x, position.y - 1, position.z));
				break;
			}
			case Direction::Left:
			{
				transform->SetPosition(D3DXVECTOR3(position.x + 1, position.y, position.z));
				break;
			}
			}
		}
	}

}

void InGameScene::Update()
{
	Input();
	Scene::Update();
	tile_layer->SetActive(false);
}

void InGameScene::Destroy()
{
	Scene::Destroy();
}
