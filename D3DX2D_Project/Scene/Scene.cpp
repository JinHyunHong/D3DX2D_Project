#include "stdafx.h"
#include "Scene.h"
#include "Scene/Actor.h"
#include "Scene/Component/TransformComponent.h"
#include "Scene/Component/CameraComponent.h"
#include "Scene/Component/MeshRendererComponent.h"
#include "Scene/Component/MoveScriptComponent.h"
#include "Scene/Component/AIScriptComponent.h"
#include "Scene/Component/AnimatorComponent.h"

Scene::Scene(Tool* const tool) :
	tool(tool)
{
	auto camera = CreateActor();
	camera->SetName("MainCamera");
	camera->AddComponent<CameraComponent>();

	auto player = CreateActor();
	player->SetName("Player");
	player->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3{ +100.0f, 0.0f, 0.0f });
	player->AddComponent<MeshRendererComponent>();
	player->AddComponent<MoveScriptComponent>();
	auto animator = player->AddComponent<AnimatorComponent>();
	animator->AddAnimation("Assets/Animation/Idle.xml");
	animator->SetAnimationMode(AnimationMode::Play);
	animator->SetCurrentAnimation("Idle");

	auto monster = CreateActor();
	monster->SetName("Monster");
	monster->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3{ 100.0f, 100.0f, 1.0f });
	monster->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3{ -100.0f, 0.0f, 0.0f });
	monster->AddComponent<MeshRendererComponent>();
	monster->AddComponent<AIScriptComponent>();
}

Scene::~Scene()
{
	CLEAR_VECTOR(actors);
}

void Scene::Update()
{
	if (!is_active)
		return;
	
	for (const auto& actor : actors)
	{
		if (!actor->IsActive())
			continue;

		actor->Update();
	}
}

auto Scene::CreateActor(bool is_active) -> std::shared_ptr<Actor>
{
	auto new_actor = std::make_shared<Actor>(tool);

	if (!new_actor->Initialize())
	{
		assert(false);
		return nullptr;
	}

	new_actor->SetActive(is_active);

	return actors.emplace_back(new_actor);
}
