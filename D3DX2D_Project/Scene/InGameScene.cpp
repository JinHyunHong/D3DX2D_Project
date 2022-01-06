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
#include "Scene/Component/TextureComponent.h"

InGameScene::InGameScene(Tool* const tool) :
	Scene(tool)
{
	camera->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// Load New Map
	LoadFromFile("Assets/Xml/Map/New_Map.xml", "World_Map", true);

	// World Object Settings
	auto object_layer = CreateLayer("Object");
	auto Item_1 = LoadTextureActor("Item_1", object_layer.get(), "Assets/Xml/Texture/Items.xml", 
		"Boss_Key", D3DXVECTOR3(2.0f, 2.0f, 0.0f), D3DXVECTOR3(400.0f, 107.0f, 0.0f));
	Item_1->AddComponent<ColliderComponent>()->SetOffsetScale(D3DXVECTOR3(30.0f, 40.0f, 0.0f));
	Item_1->GetComponent<ColliderComponent>()->SetColor(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));

	auto Item_2 = LoadTextureActor("Item_2", object_layer.get(), "Assets/Xml/Texture/Items.xml",
		"Sword", D3DXVECTOR3(2.0f, 2.0f, 0.0f), D3DXVECTOR3(230.0f, 300.0f, 0.0f));
	Item_2->AddComponent<ColliderComponent>()->SetOffsetScale(D3DXVECTOR3(30.0f, 40.0f, 0.0f));
	Item_2->GetComponent<ColliderComponent>()->SetColor(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));


	// Player Settings
	player = object_layer->CreateActor();
	player->SetName("Player");
	player->AddComponent<ColliderComponent>()->SetOffsetScale(D3DXVECTOR3(30.0f, 50.0f, 0.0f));
	player->GetComponent<ColliderComponent>()->SetColor(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
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

	// Enemy Settings
	auto enemy = object_layer->CreateActor();
	enemy->SetName("Enemy_1");
	enemy->AddComponent<ColliderComponent>()->SetOffsetScale(D3DXVECTOR3(30.0f, 50.0f, 0.0f));
	enemy->GetComponent<ColliderComponent>()->SetColor(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
	enemy->AddComponent<MeshRendererComponent>();
	enemy->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(2.0f, 2.0f, 1.0f));
	enemy->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(100.0f, 420.0f, 0.0f));
	animator = enemy->AddComponent<AnimatorComponent>();
	animator->AddAnimation("Assets/Xml/Animation/Knight1_Idle_Left.xml");
	animator->SetAnimationMode(AnimationMode::Play);
	animator->SetCurrentAnimation("Idle_Left");

	// Hud Settings
	hud_layer = CreateLayer("HUD");
	hud = hud_layer->CreateActor();
	hud->SetName("HUD");
	hud->AddComponent<MeshRendererComponent>();
	hud->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(2.0f, 2.0f, 1.0f));
	hud->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	auto texture = hud->AddComponent<TextureComponent>();
	texture->AddTexture("Assets/Xml/Texture/HUD.xml");
	texture->SetCurrentTexture("HUD");
	hud->AddComponent<TextRendererComponent>()->AddText("Jewel", "000", 
		D3DXCOLOR(255.0f, 255.0f, 255.0f, 1.0f), D3DXVECTOR2(0.6f, 0.6f), D3DXVECTOR2(137.0f, 42.0f));
	hud->AddComponent<TextRendererComponent>()->AddText("Bomb", "00", 
		D3DXCOLOR(255.0f, 255.0f, 255.0f, 1.0f), D3DXVECTOR2(0.6f, 0.6f), D3DXVECTOR2(197.0f, 42.0f));
	hud->AddComponent<TextRendererComponent>()->AddText("Arrow", "00", 
		D3DXCOLOR(255.0f, 255.0f, 255.0f, 1.0f), D3DXVECTOR2(0.6f, 0.6f), D3DXVECTOR2(245.0f, 42.0f));
	hud->AddComponent<TextRendererComponent>()->AddText("Key", "00", 
		D3DXCOLOR(255.0f, 255.0f, 255.0f, 1.0f), D3DXVECTOR2(0.6f, 0.6f), D3DXVECTOR2(285.0f, 42.0f));

	auto heart_0 = LoadTextureActor("Heart_0", hud_layer.get(),"Assets/Xml/Texture/Heart.xml", 
		"Heart_Full", D3DXVECTOR3(2.0f, 2.0f, 0.0f), D3DXVECTOR3(353.0f, 47.0f, 0.0f));
	auto heart_1 = LoadTextureActor("Heart_1", hud_layer.get(),"Assets/Xml/Texture/Heart.xml", 
		"Heart_Full", D3DXVECTOR3(2.0f, 2.0f, 0.0f), D3DXVECTOR3(373.0f, 47.0f, 0.0f));
	auto heart_2 = LoadTextureActor("Heart_2", hud_layer.get(),"Assets/Xml/Texture/Heart.xml", 
		"Heart_Full", D3DXVECTOR3(2.0f, 2.0f, 0.0f), D3DXVECTOR3(393.0f, 47.0f, 0.0f));
	auto heart_3 = LoadTextureActor("Heart_3", hud_layer.get(),"Assets/Xml/Texture/Heart.xml", 
		"Heart_Full", D3DXVECTOR3(2.0f, 2.0f, 0.0f), D3DXVECTOR3(413.0f, 47.0f, 0.0f));
	auto heart_4 = LoadTextureActor("Heart_4", hud_layer.get(),"Assets/Xml/Texture/Heart.xml", 
		"Heart_Full", D3DXVECTOR3(2.0f, 2.0f, 0.0f), D3DXVECTOR3(433.0f, 47.0f, 0.0f));

	hearts.emplace_back(heart_0);
	hearts.emplace_back(heart_1);
	hearts.emplace_back(heart_2);
	hearts.emplace_back(heart_3);
	hearts.emplace_back(heart_4);

	// Status(Inventory) Settings
	auto status_back = hud_layer->CreateActor();
	status_back->SetName("Status_Back");
	status_back->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(2.0f, 2.0f, 1.0f));
	status_back->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(-7.0f, -500.0f, 0.0f));
	status_back->AddComponent<MeshRendererComponent>();
	texture = status_back->AddComponent<TextureComponent>();
	texture->AddTexture("Assets/Xml/Texture/Status_Back.xml");
	texture->SetCurrentTexture("Status_Back");


	hud->GetComponent<TransformComponent>()->SetParent(camera->GetComponent<TransformComponent>().get());
	heart_0->GetComponent<TransformComponent>()->SetParent(camera->GetComponent<TransformComponent>().get());
	heart_1->GetComponent<TransformComponent>()->SetParent(camera->GetComponent<TransformComponent>().get());
	heart_2->GetComponent<TransformComponent>()->SetParent(camera->GetComponent<TransformComponent>().get());
	heart_3->GetComponent<TransformComponent>()->SetParent(camera->GetComponent<TransformComponent>().get());
	heart_4->GetComponent<TransformComponent>()->SetParent(camera->GetComponent<TransformComponent>().get());
	status_back->GetComponent<TransformComponent>()->SetParent(camera->GetComponent<TransformComponent>().get());
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


	
	//Key Input
	auto input_manager = tool->GetManager<SubsystemManager>()->GetSubsystem<InputManager>();
	auto delta_time = timer->GetDeltaTimeMs();

	if (input_manager->GetKeyDown("Status"))
	{
		is_open = !is_open;
	}

	auto hud_transform = hud->GetComponent<TransformComponent>();
	auto position = Math::Vec3_Abs(new_position, hud_transform->GetPosition());
	
	if (is_open && std::round(position.y) < 500.0f)
	{
		hud_layer->SetOffsetPosition(D3DXVECTOR3(0.0f, 0.4f * delta_time, 0.0f));
	}

	else if (!is_open && position.y > 10.0f)
	{
		hud_layer->SetOffsetPosition(D3DXVECTOR3(position.x, -(0.4f * delta_time), 0.0f));
	}

}

void InGameScene::Update()
{
	Scene::Update();
	tile_layer->SetActive(false);
}

void InGameScene::Destroy()
{
	Scene::Destroy();
}

auto InGameScene::LoadTextureActor(const std::string& name, Layer* const layer,
	const std::string& path, const std::string& curent_texture_name, const D3DXVECTOR3& scale, 
	const D3DXVECTOR3& position) -> const actor_pointer
{
	auto new_actor = layer->CreateActor();
	new_actor->SetName(name);
	new_actor->GetComponent<TransformComponent>()->SetScale(scale);
	new_actor->GetComponent<TransformComponent>()->SetPosition(position);
	new_actor->AddComponent<MeshRendererComponent>();
	auto texture = new_actor->AddComponent<TextureComponent>();
	texture->AddTextures(path);
	texture->SetCurrentTexture(curent_texture_name);

	return new_actor;
}