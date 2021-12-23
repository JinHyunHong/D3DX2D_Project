#include "stdafx.h"
#include "MenuScene.h"
#include "Scene/Actor.h"
#include "Scene/Component/TransformComponent.h"
#include "Scene/Component/MeshRendererComponent.h"
#include "Scene/Component/AnimatorComponent.h"

MenuScene::MenuScene(class Tool* const tool) :
	Scene(tool)
{
	auto graphics = tool->GetManager<SubsystemManager>()->GetSubsystem<D3D11_Base>();
	graphics->SetBackClearColor(0xff38385e);

	auto select_character = CreateActor();
	select_character->SetName("Background");
	select_character->AddComponent<MeshRendererComponent>();
	select_character->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(3.0f, 2.3f, 1.0f));
	select_character->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(-70.0f, 0.0f, 0.0f));
	auto animator = select_character->AddComponent<AnimatorComponent>();
	animator->AddAnimation("Assets/Animation/SelectCharacter.xml");
	animator->SetAnimationMode(AnimationMode::Play);
	animator->SetCurrentAnimation("SelectCharacter");

	move_mouse = CreateActor();
	move_mouse->SetName("MoveMouse");
	move_mouse->AddComponent<MeshRendererComponent>();
	move_mouse->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(2.5f, 2.5f, 1.0f));
	move_mouse->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(-120.0f, 75.0f, 0.0f));
	animator = move_mouse->AddComponent<AnimatorComponent>();
	animator->AddAnimation("Assets/Animation/MoveMouse.xml");
	animator->SetAnimationMode(AnimationMode::Play);
	animator->SetCurrentAnimation("MoveMouse");
}

MenuScene::~MenuScene()
{
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
				position.y -= 70;
			}

			else if (slot_index < SLOT_NUM - 1)
			{
				position.x -= 60;
				position.y -= 90;
			}

			else
			{
				position.y -= 40;
			}
		}
		else if ((GetAsyncKeyState(VK_UP) & 0x8000) && slot_index > 0)
		{
			--slot_index;

			if (slot_index < SLOT_NUM - 3)
			{
				position.y += 70;
			}

			else if (slot_index < SLOT_NUM - 2)
			{
				position.x += 60;
				position.y += 90;
			}

			else
				position.y += 40;
		}

		transform->SetPosition(position);
		frame_counter = 0.0f;
	}

}

void MenuScene::Update()
{
	Input();
	Scene::Update();
}

void MenuScene::Destroy()
{
	Scene::Destroy();

	//auto graphics = tool->GetManager<SubsystemManager>()->GetSubsystem<D3D11_Base>();
	//graphics->ClearColor();
}
