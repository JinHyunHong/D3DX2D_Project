#include "stdafx.h"
#include "MoveScriptComponent.h"
#include "Scene/Actor.h"
#include "TransformComponent.h"
#include "AnimatorComponent.h"

MoveScriptComponent::MoveScriptComponent(class Tool* const tool, class Actor* const actor,
	class TransformComponent* const transform) :
	IComponent(tool, actor, transform)
{
}

bool MoveScriptComponent::Initialize()
{
	return true;
}

void MoveScriptComponent::Update()
{
	auto position = transform->GetPosition();
	auto animator = actor->GetComponent<AnimatorComponent>();

	if (GetAsyncKeyState('W') & 0x8000)
	{
		position.y++;
		animator->SetCurrentAnimation("Idle_Up");
	}
	else if (GetAsyncKeyState('S') & 0x8000)
	{
		position.y--;
		animator->SetCurrentAnimation("Idle_Down");
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		position.x++;
		animator->SetCurrentAnimation("Idle_Right");
	}
	else if (GetAsyncKeyState('A') & 0x8000)
	{
		position.x--;
		animator->SetCurrentAnimation("Idle_Left");
	}

	transform->SetPosition(position);
}

void MoveScriptComponent::Destroy()
{
}
