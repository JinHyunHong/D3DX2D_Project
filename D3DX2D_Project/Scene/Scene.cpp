#include "stdafx.h"
#include "Scene.h"

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
}

void Scene::CreateActor(const std::shared_ptr<class Actor>& actor, bool is_active)
{
}
