#include "stdafx.h"
#include "ColliderComponent.h"
#include "Scene/Actor.h"
#include "Scene/Component/TransformComponent.h"

ColliderComponent::ColliderComponent(Tool* const tool, Actor* const actor, 
	TransformComponent* const transform) :
	IRendererComponent(tool, actor, transform)
{
}

bool ColliderComponent::Initialize()
{
	IRendererComponent::Initialize();

	return true;
}

void ColliderComponent::Update()
{
}

void ColliderComponent::Destroy()
{
	ClearOverlapActors();
}

bool ColliderComponent::IsCollision(Actor* const dest)
{
	if (!actor->IsActive() || !dest->IsActive())
		return false;
	
	auto dest_collision = dest->GetComponent<ColliderComponent>();
	
	if (!dest_collision)
		return false;

	if (actor->GetName() == "Scope")
		printf("s");

	auto src_transform = actor->GetComponent<TransformComponent>();
	auto dest_transform = dest->GetComponent<TransformComponent>();

	auto src_min = (src_transform->GetPosition() + offset_position) - ((src_transform->GetScale() + offset_scale) * 0.5f);
	auto src_max = (src_transform->GetPosition() + offset_position) + ((src_transform->GetScale() + offset_scale) * 0.5f);

	auto dest_min = (dest_transform->GetPosition() + dest_collision->GetOffsetPosition()) - ((dest_transform->GetScale() + dest_collision->GetOffsetScale()) * 0.5f);
	auto dest_max = (dest_transform->GetPosition() + dest_collision->GetOffsetPosition()) + ((dest_transform->GetScale() + dest_collision->GetOffsetScale()) * 0.5f);

	if (src_max.x < dest_min.x || src_min.x > dest_max.x ||
		src_max.y < dest_min.y || src_min.y > dest_max.y)
		return false;
	else
	{
		AddOverlapActor(dest);
		dest_collision->AddOverlapActor(actor);
		return true;
	}
}

bool ColliderComponent::GetOverlapActor(const std::string& name)
{
	for (const auto& actor : overlap_actors)
	{
		if (actor->GetName() == name)
			return true;
	}

	return false;
}

auto ColliderComponent::GetOverlapActor_back() -> class Actor* const
{
	if (overlap_actors.empty())
		return nullptr;
	return overlap_actors[overlap_actors.size() - 1];
}

void ColliderComponent::ClearOverlapActors()
{
	CLEAR_VECTOR(overlap_actors);
}

void ColliderComponent::AddOverlapActor(Actor* const dest)
{
	if (GetOverlapActor(dest->GetName()))
		return;

	overlap_actors.push_back(dest);
}
