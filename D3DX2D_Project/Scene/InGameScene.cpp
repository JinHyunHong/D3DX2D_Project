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
	camera->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// Load New Map
	LoadFromFile("Assets/Xml/Map/New_Map.xml", "World_Map", true);

	// Player Settings
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


	// Hud Settings
	auto hud_layer = CreateLayer("HUD");
	hud = hud_layer->CreateActor();
	hud->SetName("HUD");
	hud->AddComponent<MeshRendererComponent>();
	hud->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(2.0f, 2.0f, 1.0f));
	hud->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	animator = hud->AddComponent<AnimatorComponent>();
	animator->AddAnimation("Assets/Xml/Animation/HUD.xml");
	animator->SetCurrentAnimation("HUD");
	hud->AddComponent<TextRendererComponent>()->AddText("Jewel", "000", D3DXCOLOR(255.0f, 255.0f, 255.0f, 1.0f), D3DXVECTOR2(0.6f, 0.6f), D3DXVECTOR2(137.0f, 42.0f));
	hud->AddComponent<TextRendererComponent>()->AddText("Bomb", "00", D3DXCOLOR(255.0f, 255.0f, 255.0f, 1.0f), D3DXVECTOR2(0.6f, 0.6f), D3DXVECTOR2(197.0f, 42.0f));
	hud->AddComponent<TextRendererComponent>()->AddText("Arrow", "00", D3DXCOLOR(255.0f, 255.0f, 255.0f, 1.0f), D3DXVECTOR2(0.6f, 0.6f), D3DXVECTOR2(245.0f, 42.0f));
	hud->AddComponent<TextRendererComponent>()->AddText("Key", "00", D3DXCOLOR(255.0f, 255.0f, 255.0f, 1.0f), D3DXVECTOR2(0.6f, 0.6f), D3DXVECTOR2(285.0f, 42.0f));

	hud->GetComponent<TransformComponent>()->SetParent(camera->GetComponent<TransformComponent>().get());
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
	// Camera Scroll Settings
	auto camera_transform = camera->GetComponent<TransformComponent>();
	auto camera_position = camera_transform->GetPosition();
	
	auto transform = player->GetComponent<TransformComponent>();
	auto player_position = player->GetComponent<TransformComponent>()->GetPosition();
	auto new_position = player_position - camera_pivot * D3DXVECTOR3(window_width, window_height, 0);

	if (new_position.x < 0.0f)
		new_position.x = 0;

	else if (new_position.x + window_width > width)
		new_position.x = width - window_width;

	if (new_position.y < 0.0f)
		new_position.y = 0;

	else if (new_position.y + window_height > height)
		new_position.y = height - window_height;
	
	camera_transform->SetPosition(new_position);


	// Player Tile Collision Settings
	auto size = player->GetComponent<ColliderComponent>()->GetOffsetScale();
	auto left = tile_layer->GetActor(GetTileIndex(D3DXVECTOR2(player_position.x, player_position.y + size.y / 2)));
	auto right = tile_layer->GetActor(GetTileIndex(D3DXVECTOR2(player_position.x + size.x, player_position.y + size.y / 2)));
	auto top = tile_layer->GetActor(GetTileIndex(D3DXVECTOR2(player_position.x + size.x / 2, player_position.y)));
	auto bottom = tile_layer->GetActor(GetTileIndex(D3DXVECTOR2(player_position.x + size.x / 2, player_position.y + size.y)));
	

	std::shared_ptr<TransformComponent> tile_transform;
	D3DXVECTOR3 tile_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 offset_scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	if (!left->GetComponent<TileRendererComponent>()->GetTile()->IsMove())
	{
		tile_transform = left->GetComponent<TransformComponent>();
		offset_scale = left->GetComponent<ColliderComponent>()->GetOffsetScale();
		tile_position = tile_transform->GetPosition() + tile_transform->GetScale() + offset_scale;
		player_position.x = player_position.x + abs(player_position.x - tile_position.x);
	}

	else if (!right->GetComponent<TileRendererComponent>()->GetTile()->IsMove())
	{
		tile_transform = right->GetComponent<TransformComponent>();
		tile_position = tile_transform->GetPosition();
		player_position.x = player_position.x - abs(player_position.x + size.x - tile_position.x);
	}

	if (!top->GetComponent<TileRendererComponent>()->GetTile()->IsMove())
	{
		tile_transform = top->GetComponent<TransformComponent>();
		offset_scale = top->GetComponent<ColliderComponent>()->GetOffsetScale();
		tile_position = tile_transform->GetPosition() + tile_transform->GetScale() + offset_scale;
		player_position.y = player_position.y + abs(player_position.y - tile_position.y);
	}

	else if (!bottom->GetComponent<TileRendererComponent>()->GetTile()->IsMove())
	{
		tile_transform = bottom->GetComponent<TransformComponent>();
		tile_position = tile_transform->GetPosition();
		player_position.y = player_position.y - abs(player_position.y + size.y - tile_position.y);
	}
	
	transform->SetPosition(player_position);

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
