#include "stdafx.h"
#include "Scene.h"
#include "Actor.h"

Scene::Scene(Tool* const tool) :
	tool(tool)
{
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
