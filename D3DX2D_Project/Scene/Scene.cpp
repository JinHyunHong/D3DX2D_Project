#include "stdafx.h"
#include "Scene.h"
#include "Layer/Layer.h"
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

	auto camera_layer = CreateLayer("MainCamera");

	camera = camera_layer->CreateActor();
	camera->SetName("MainCamera");
	camera->AddComponent<CameraComponent>();
}

Scene::~Scene()
{
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

	for (const auto& layer : layers)
	{
		layer->Update(renderer);
	}
}

void Scene::Destroy()
{
	renderer->ClearRenderables();
}

auto Scene::CreateLayer(const std::string& name, bool is_active) -> std::shared_ptr<class Layer>
{
	auto new_layer = std::make_shared<Layer>(tool);

	if (!new_layer->Initialize())
	{
		assert(false);
		return nullptr;
	}

	new_layer->SetName(name);
	new_layer->SetActive(is_active);

	return layers.emplace_back(new_layer);
}
