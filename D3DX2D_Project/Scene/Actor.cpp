#include "stdafx.h"
#include "Actor.h"
#include "Component/TransformComponent.h"
#include "Component/ColliderComponent.h"

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

void Actor::Update(const std::shared_ptr<Actor>& dest)
{
	if (!is_active)
		return;

	// 충돌 처리
	if (!colliders.empty() && dest)
	{
		for (const auto& collider : colliders)
		{
			if (!collider->IsEnable())
				continue;
			
			collider->IsCollision(dest.get());
		}
	}

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