#include "stdafx.h"
#include "Actor.h"
#include "Component/IComponent.h"

Actor::Actor(Tool* const tool) :
	tool(tool)
{
	AddComponent<TransformComponent>();
}

Actor::~Actor()
{
	CLEAR_VECTOR(components);
}

bool Actor::Initialize()
{
	return true;
}

void Actor::Update()
{
	if (!is_active)
		return;

	for (const auto& component : components)
	{
		if (!component->IsEnable())
			continue;

		component->Update();
	}
}

void Actor::Destroy()
{
	for (const auto& component : components)
		component->Destroy();
}