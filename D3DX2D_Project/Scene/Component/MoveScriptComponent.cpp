#include "stdafx.h"
#include "MoveScriptComponent.h"
#include "TransformComponent.h"

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

	if (GetAsyncKeyState('W') & 0x8000)		 position.y++;
	else if (GetAsyncKeyState('S') & 0x8000) position.y--;
	if (GetAsyncKeyState('D') & 0x8000)		 position.x++;
	else if (GetAsyncKeyState('A') & 0x8000) position.x--;

	transform->SetPosition(position);
}

void MoveScriptComponent::Destroy()
{
}
