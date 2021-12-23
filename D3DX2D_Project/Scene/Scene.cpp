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
	renderer = tool->GetManager<SubsystemManager>()->GetSubsystem<Renderer>();
	timer = tool->GetManager<SubsystemManager>()->GetSubsystem<Timer>();
	graphics = tool->GetManager<SubsystemManager>()->GetSubsystem<D3D11_Base>();

	auto camera = CreateActor();
	camera->SetName("MainCamera");
	camera->AddComponent<CameraComponent>();
}

Scene::~Scene()
{
	CLEAR_VECTOR(actors);
}

void Scene::Initialize()
{
}

void Scene::Input()
{
}

void Scene::Update()
{
	if (!is_active)
		return;

	Input();

	for (const auto& actor : actors)
	{
		actor->Update();
	}

	if (is_update)
	{
		renderer->UpdateRenderables(this);
		is_update = false;
	}
}

void Scene::Destroy()
{
	renderer->ClearRenderables();
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
