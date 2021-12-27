#include "stdafx.h"
#include "ColliderComponent.h"
#include "Scene/Actor.h"
#include "Scene/Component/TransformComponent.h"

ColliderComponent::ColliderComponent(Tool* const tool, Actor* const actor, 
	TransformComponent* const transform) :
	IComponent(tool, actor, transform)
{
}

bool ColliderComponent::Initialize()
{
	return true;
}

void ColliderComponent::Update()
{
#ifdef _DEBUG
	HDC hdc = GetDC(Core::GetInst().GetWindow()->GetWindowHandle());
	Rectangle(hdc, )
#endif
}

void ColliderComponent::Destroy()
{
}

bool ColliderComponent::IsCollision(class Actor* const src, class Actor* const dest)
{
	if (!src->IsActive() || !dest->IsActive())
		return false;

	auto src_transform = src->GetComponent<TransformComponent>();
	auto dest_transform = dest->GetComponent<TransformComponent>();

	auto src_min = src_transform->GetPosition() - (src_transform->GetScale() * 0.5f);
	auto src_max = src_transform->GetPosition() + (src_transform->GetScale() * 0.5f);

	auto dest_min = dest_transform->GetPosition() - (dest_transform->GetScale() * 0.5f);
	auto dest_max = dest_transform->GetPosition() + (dest_transform->GetScale() * 0.5f);

	if (src_max.x < dest_min.x || src_min.x > dest_max.x ||
		src_max.y < dest_min.y || src_min.y > dest_max.y)
		return false;
	else
		return true;
}
