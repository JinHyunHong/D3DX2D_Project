#include "stdafx.h"
#include "NameSelectScene.h"
#include "Scene/Layer/Layer.h"
#include "Actor.h"
#include "Scene/Component/TransformComponent.h"
#include "Scene/Component/MeshRendererComponent.h"
#include "Scene/Component/AnimatorComponent.h"
#include "Scene/Component/TextRendererComponent.h"

NameSelectScene::NameSelectScene(Tool* const tool) :
	Scene(tool)
{
	auto text_layer = CreateLayer("Select_Text");
	auto register_name = text_layer->CreateActor();
	register_name->SetName("RegisterName");
	register_name->AddComponent<MeshRendererComponent>();
	register_name->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(2.0f, 2.3f, 1.0f));
	register_name->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(-20.0f, 150.0f, 0.0f));
	auto animator = register_name->AddComponent<AnimatorComponent>();
	animator->AddAnimation("Assets/Animation/RegisterName.xml");
	animator->SetAnimationMode(AnimationMode::Play);
	animator->SetCurrentAnimation("RegisterName");

	auto board_layer = CreateLayer("board");	
	name_board = board_layer->CreateActor();
	auto board_transform = name_board->GetComponent<TransformComponent>();
	board_transform->SetPosition(D3DXVECTOR3(100.0f, 270.0f, 0.0f));

	auto A = board_layer->CreateActor();
	auto text_renderer = A->AddComponent<TextRendererComponent>();
	text_renderer->AddText("A", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(100.0f, 270.0f));
	A->GetComponent<TransformComponent>()->SetParent(board_transform.get());
	
	auto scope_layer = CreateLayer("Scope");
	scope = scope_layer->CreateActor();
	scope->SetName("Scope");
	scope->AddComponent<MeshRendererComponent>();
	scope->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(1.91f, 2.0f, 1.0f));
	scope->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(-5.0f, -100.0f, 0.0f));
	animator = scope->AddComponent<AnimatorComponent>();
	animator->AddAnimation("Assets/Animation/Scope.xml");
	animator->SetAnimationMode(AnimationMode::Play);
	animator->SetCurrentAnimation("Scope");

	auto back_layer = CreateLayer("Background");
	auto select_name = back_layer->CreateActor();
	select_name->SetName("NameSelectBackground");
	select_name->AddComponent<MeshRendererComponent>();
	select_name->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(2.0f, 2.3f, 1.0f));
	select_name->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	animator = select_name->AddComponent<AnimatorComponent>();
	animator->AddAnimation("Assets/Animation/SelectName.xml");
	animator->SetAnimationMode(AnimationMode::Play);
	animator->SetCurrentAnimation("NameSelectBackground");
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
	auto scope_transform = scope->GetComponent<TransformComponent>();
	auto board_position = board_transform->GetPosition();
	auto scope_position = scope_transform->GetPosition();
	
	if (frame_counter > 0.05)
	{
		if ((GetAsyncKeyState('A') & 0x8000))
		{
			board_position.x += 10;
		}
		else if ((GetAsyncKeyState('D') & 0x8000))
		{
			board_position.x -= 10;
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
		scope_transform->SetPosition(scope_position);
		frame_counter = 0.0f;
	}

	if (GetAsyncKeyState('V') & 0x8000)
	{
		auto scene_manager = tool->GetManager<SubsystemManager>()->GetSubsystem<SceneManager>();
		scene_manager->SetCurrentScene("InGame");
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
