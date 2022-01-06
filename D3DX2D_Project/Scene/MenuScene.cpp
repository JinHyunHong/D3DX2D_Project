#include "stdafx.h"
#include "MenuScene.h"
#include "Scene/Actor.h"
#include "Layer/Layer.h"
#include "Scene/Component/TransformComponent.h"
#include "Scene/Component/MeshRendererComponent.h"
#include "Scene/Component/AnimatorComponent.h"
#include "Scene/Component/TextRendererComponent.h"

MenuScene::MenuScene(class Tool* const tool) :
	Scene(tool)
{
	auto back_layer = CreateLayer("Background");
	auto select_character = back_layer->CreateActor();
	select_character->SetName("Background");
	select_character->AddComponent<MeshRendererComponent>();
	select_character->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(2.4f, 2.0f, 1.0f));
	select_character->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	auto animator = select_character->AddComponent<AnimatorComponent>();
	animator->AddAnimation("Assets/Xml/Animation/SelectCharacter.xml");
	animator->SetAnimationMode(AnimationMode::Play);
	animator->SetCurrentAnimation("SelectCharacter");

	auto mouse_layer = CreateLayer("Mouse");
	move_mouse = mouse_layer->CreateActor();
	move_mouse->SetName("MoveMouse");
	move_mouse->AddComponent<MeshRendererComponent>();
	move_mouse->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(2.5f, 2.5f, 1.0f));
	move_mouse->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(150.0f, 140.0f, 0.0f));
	animator = move_mouse->AddComponent<AnimatorComponent>();
	animator->AddAnimation("Assets/Xml/Animation/MoveMouse.xml");
	animator->SetAnimationMode(AnimationMode::Play);
	animator->SetCurrentAnimation("MoveMouse");

	auto map_editor = mouse_layer->CreateActor();
	map_editor->SetName("map_editor_text");
	map_editor->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(10.0f, 450.0f, 0.0f));
	map_editor->AddComponent<TextRendererComponent>()->AddText("Base", "1 : MapEditor",
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.8f, 0.8f));
}

MenuScene::~MenuScene()
{
}

void MenuScene::Initialize()
{
	Scene::Initialize();

	graphics->SetBackClearColor(0xff38385e);
}

void MenuScene::Input()
{
	frame_counter += timer->GetDeltaTimeSec();
	auto transform = move_mouse->GetComponent<TransformComponent>();
	auto position = transform->GetPosition();

	if (frame_counter > 0.3)
	{
		if ((GetAsyncKeyState(VK_DOWN) & 0x8000) && slot_index < SLOT_NUM - 1)
		{
			++slot_index;

			if (slot_index < SLOT_NUM - 2)
			{
				position.y += 65;
			}

			else if (slot_index < SLOT_NUM - 1)
			{
				position.x -= 50;
				position.y += 80;
			}

			else
			{
				position.y += 30;
			}
		}
		else if ((GetAsyncKeyState(VK_UP) & 0x8000) && slot_index > 0)
		{
			--slot_index;

			if (slot_index < SLOT_NUM - 3)
			{
				position.y -= 65;
			}

			else if (slot_index < SLOT_NUM - 2)
			{
				position.x += 50;
				position.y -= 80;
			}

			else
				position.y -= 30;
		}


		if (GetAsyncKeyState('X') & 0x8000)
		{
			switch (static_cast<Slot_Type>(slot_index))
			{
			case Slot_Type::One:
			case Slot_Type::Two:
			case Slot_Type::Three:
			{
				auto scene_manager = tool->GetManager<SubsystemManager>()->GetSubsystem<SceneManager>();
				scene_manager->SetCurrentScene("NameSelect");
				break;
			}
			case Slot_Type::Copy_Player:
				break;
			case Slot_Type::Erase_Player:
				break;
			}
		}
		transform->SetPosition(position);
		frame_counter = 0.0f;
	}

	// ¸Ê ¿¡µðÅÍ ¾À Àå¸é ÀüÈ¯
	if (GetAsyncKeyState('1') & 0x8000)
	{
		auto scene_manager = tool->GetManager<SubsystemManager>()->GetSubsystem<SceneManager>();
		scene_manager->SetCurrentScene("MapEditor");
	}
}

void MenuScene::Update()
{
	Scene::Update();
}

void MenuScene::Destroy()
{
	Scene::Destroy();

	//TODO :
	//auto graphics = tool->GetManager<SubsystemManager>()->GetSubsystem<D3D11_Base>();
	//graphics->ClearColor();
}
