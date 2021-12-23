#include "stdafx.h"
#include "NameSelectScene.h"
#include "Actor.h"
#include "Scene/Component/TransformComponent.h"
#include "Scene/Component/MeshRendererComponent.h"
#include "Scene/Component/AnimatorComponent.h"

NameSelectScene::NameSelectScene(Tool* const tool) :
	Scene(tool)
{
	auto register_name = CreateActor();
	register_name->SetName("RegisterName");
	register_name->AddComponent<MeshRendererComponent>();
	register_name->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(2.0f, 2.3f, 1.0f));
	register_name->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(-20.0f, 150.0f, 0.0f));
	auto animator = register_name->AddComponent<AnimatorComponent>();
	animator->AddAnimation("Assets/Animation/RegisterName.xml");
	animator->SetAnimationMode(AnimationMode::Play);
	animator->SetCurrentAnimation("RegisterName");


	name_board = CreateActor();
	name_board->SetName("NameBoard");
	name_board->AddComponent<MeshRendererComponent>();
	name_board->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(2.0f, 2.3f, 1.0f));
	name_board->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(-170.0f, -110.0f, 0.0f));
	animator = name_board->AddComponent<AnimatorComponent>();
	animator->AddAnimation("Assets/Animation/NameBoard.xml");
	animator->SetAnimationMode(AnimationMode::Play);
	animator->SetCurrentAnimation("NameBoard");

	name_board_small = CreateActor();
	name_board_small->SetName("NameBoard_Small");
	name_board_small->AddComponent<MeshRendererComponent>();
	name_board_small->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(2.0f, 2.3f, 1.0f));
	name_board_small->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(+170.0f, -70.0f, 0.0f));
	animator = name_board_small->AddComponent<AnimatorComponent>();
	animator->AddAnimation("Assets/Animation/NameBoard_Small.xml");
	animator->SetAnimationMode(AnimationMode::Play);
	animator->SetCurrentAnimation("NameBoard_Small");


	auto select_name = CreateActor();
	select_name->SetName("NameSelectBackground");
	select_name->AddComponent<MeshRendererComponent>();
	select_name->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(2.0f, 2.3f, 1.0f));
	select_name->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	animator = select_name->AddComponent<AnimatorComponent>();
	animator->AddAnimation("Assets/Animation/SelectName.xml");
	animator->SetAnimationMode(AnimationMode::Play);
	animator->SetCurrentAnimation("NameSelectBackground");

	scope = CreateActor();
	scope->SetName("Scope");
	scope->AddComponent<MeshRendererComponent>();
	scope->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(1.91f, 2.0f, 1.0f));
	scope->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(-5.0f, -100.0f, 0.0f));
	animator = scope->AddComponent<AnimatorComponent>();
	animator->AddAnimation("Assets/Animation/Scope.xml");
	animator->SetAnimationMode(AnimationMode::Play);
	animator->SetCurrentAnimation("Scope");
}

NameSelectScene::~NameSelectScene()
{
}

void NameSelectScene::Initialize()
{
	Scene::Initialize();

	graphics->SetBackClearColor(0x000000);
}

void NameSelectScene::Input()
{
	frame_counter += timer->GetDeltaTimeSec();
	auto board_transform = name_board->GetComponent<TransformComponent>();
	auto small_transform = name_board_small->GetComponent<TransformComponent>();
	auto scope_transform = scope->GetComponent<TransformComponent>();
	auto board_position = board_transform->GetPosition();
	auto small_position = small_transform->GetPosition();
	auto scope_position = scope_transform->GetPosition();

	if (frame_counter > 0.05)
	{
		if ((GetAsyncKeyState('A') & 0x8000))
		{
			board_position.x += 10;
			small_position.x += 10;
		}
		else if ((GetAsyncKeyState('D') & 0x8000))
		{
			board_position.x -= 10;
			small_position.x -= 10;
		}

		if ((GetAsyncKeyState('W') & 0x8000) && scope_position.y < -20.0f)
		{
			scope_position.y += 3;
		}
		else if ((GetAsyncKeyState('S') & 0x8000) && scope_position.y > -200.0f)
		{
			scope_position.y -= 3;
		}

		board_transform->SetPosition(board_position);
		small_transform->SetPosition(small_position);
		scope_transform->SetPosition(scope_position);
		frame_counter = 0.0f;
	}
}

void NameSelectScene::Update()
{
	Input();
	Scene::Update();
}

void NameSelectScene::Destroy()
{
	Scene::Destroy();
}
