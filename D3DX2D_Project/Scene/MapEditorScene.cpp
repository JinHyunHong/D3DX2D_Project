#include "stdafx.h"
#include "MapEditorScene.h"
#include "Layer/Layer.h"
#include "Actor.h"
#include "Scene/Component/MeshRendererComponent.h"
#include "Scene/Component/AnimatorComponent.h"
#include "Scene/Component/TransformComponent.h"
#include "Scene/Component/TileRendererComponent.h"
#include "Scene/Component/ColliderComponent.h"
#include "Scene/Component/AnimatorComponent.h"

MapEditorScene::MapEditorScene(Tool* const tool) :
	Scene(tool)
{
}

MapEditorScene::~MapEditorScene()
{
	camera->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(100.0f, 50.0f, 0.0f));
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

	if (input_manager->GetKeyDown("Load"))
	{
		LoadFromFile("Assets/Xml/Map/New_Map.xml", "World_Map", true);
	}

	if (input_manager->GetKeyDown("Save"))
	{
		SaveToFile("Assets/Xml/Map/New_Map.xml");
	}

	transform->SetPosition(position);


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
}

void MapEditorScene::Update()
{
	Scene::Update();
	tile_layer->SetActive(false);
}

void MapEditorScene::Destroy()
{
	Scene::Destroy();
}