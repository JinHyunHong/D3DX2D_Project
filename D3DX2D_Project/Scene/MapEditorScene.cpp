#include "stdafx.h"
#include "MapEditorScene.h"
#include "Layer/Layer.h"
#include "Actor.h"
#include "Scene/Component/MeshRendererComponent.h"
#include "Scene/Component/AnimatorComponent.h"
#include "Scene/Component/TransformComponent.h"
#include "Scene/Component/TileRendererComponent.h"
#include "Scene/Component/ColliderComponent.h"

MapEditorScene::MapEditorScene(Tool* const tool) :
	Scene(tool)
{
	window_width = static_cast<float>(Core::GetInst().GetWidth());
	window_height = static_cast<float>(Core::GetInst().GetHeight());

	auto map_layer = CreateLayer("Map");
	auto map = map_layer->CreateActor();
	map->SetName("Map");
	map->AddComponent<MeshRendererComponent>();
	map->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(1.9f, 1.9f, 1.0f));
	map->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	auto animator = map->AddComponent<AnimatorComponent>();
	animator->AddAnimation("Assets/Xml/Map/World_Map.xml");
	animator->SetCurrentAnimation("World_Map");

	tile_layer = CreateLayer("Tile");
}

MapEditorScene::~MapEditorScene()
{
}

void MapEditorScene::Initialize()
{
	Scene::Initialize();

	graphics->SetBackClearColor(0xff555566);

	Core::GetInst().GetWindow()->CreateInDialog(Dialog_type::MapEditorInit, IDD_MAP_EDITOR_INIT);
}

void MapEditorScene::Input()
{
	auto transform = camera->GetComponent<TransformComponent>();
	auto position = transform->GetPosition();
	auto input_manager = tool->GetManager<SubsystemManager>()->GetSubsystem<InputManager>();
	auto delta_time = timer->GetDeltaTimeMs();
	frame_counter += delta_time;

	if (input_manager->GetKeyPress("MoveUp") && position.y > 0.0f)
	{
		position.y -= speed * delta_time;
	}

	if (input_manager->GetKeyPress("MoveDown") && position.y < height - window_height)
	{
		position.y += speed * delta_time;
	}

	if (input_manager->GetKeyPress("MoveRight") && position.x < width - window_width)
	{
		position.x += speed * delta_time;
	}

	if (input_manager->GetKeyPress("MoveLeft") && position.x > 0.0f)
	{
		position.x -= speed * delta_time;
	}

	// 카메라 Speed
	if (input_manager->GetKeyDown("Num1") && speed > 0.1f)
	{
		speed -= 0.05f;
	}

	if (input_manager->GetKeyDown("Num2") && speed < 1.0f)
	{
		speed += 0.05f;
	}

	// 타일 편집모드
	if (input_manager->GetKeyDown("Num3"))
	{
		edit_mode = Edit_Mode::NoMove;
	}

	if (input_manager->GetKeyDown("Num4"))
	{
		edit_mode = Edit_Mode::Move;
	}

	transform->SetPosition(position);


	if (frame_counter > 0.1)
	{
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(Core::GetInst().GetWindow()->GetWindowHandle(), &pt);

		if (input_manager->GetKeyDown("LButton"))
		{
			if (auto tile = tile_layer->GetActor(GetTileIndex(D3DXVECTOR2(pt.x + position.x, pt.y + position.y))))
			{
				auto tile_edit = tile->GetComponent<TileRendererComponent>()->GetTile();
				auto collider = tile->GetComponent<ColliderComponent>();
				switch (edit_mode)
				{
				case Edit_Mode::NoMove:
				{
					tile_edit->SetMove(false);
					collider->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
					break;
				}
				case Edit_Mode::Move:
				{
					tile_edit->SetMove(true);
					collider->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
					break;
				}
				}
			}
		}

		frame_counter = 0.0f;
	}

}

void MapEditorScene::Update()
{
	Input();
	Scene::Update();	
	tile_layer->SetActive(false);
}

void MapEditorScene::Destroy()
{
	Scene::Destroy();
}

void MapEditorScene::CreateTiles(const float& width, const float& height)
{
	// 969, 855
	this->width = width;
	this->height = height;

	tile_number_y = static_cast<uint>(height / 50);
	tile_number_x = static_cast<uint>(width / 50);

	for (uint i = 0; i < tile_number_y; ++i)
	{
		for (uint j = 0; j < tile_number_x; ++j)
		{
			auto new_tile = tile_layer->CreateActor();
			new_tile->SetName("tile" + std::to_string(static_cast<uint>(i * tile_number_y + j)));
			new_tile->AddComponent<ColliderComponent>()->SetOffsetScale(D3DXVECTOR3(10.0f, 10.0f, 1.0f));
			auto transform = new_tile->GetComponent<TransformComponent>();
			transform->SetScale(D3DXVECTOR3(40.0f, 40.0f, 1.0f));
			transform->SetPosition(D3DXVECTOR3(j * 50.0f, i * 50.0f, 0.0f));
			new_tile->AddComponent<TileRendererComponent>()->AddTile("Assets/Xml/Map/Empty_Tile.xml", static_cast<uint>(i * tile_number_y + j));
		}
	}
}

auto MapEditorScene::GetTileIndex(const D3DXVECTOR2& position) const -> const uint
{
	uint index_x = static_cast<uint>(position.x / 50);
	uint index_y = static_cast<uint>(position.y / 50);

	// 예외처리
	if (index_x < 0 || index_x >= tile_number_x)
		return -1;

	else if (index_y < 0 || index_y >= tile_number_y)
		return -1;

	return index_y * tile_number_x + index_x;
	
}
