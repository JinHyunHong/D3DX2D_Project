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
	if (!actor->IsActive())
		return;

	auto position = transform->GetPosition();
	auto animator = actor->GetComponent<AnimatorComponent>();
	auto input_manager = tool->GetManager<SubsystemManager>()->GetSubsystem<InputManager>();

	if (input_manager->GetKeyDown("MoveUp"))
	{
		position.y--;
		animator->SetCurrentAnimation("Idle_Up");
		direction = Direction::Up;
	}

	else if (input_manager->GetKeyPress("MoveUp"))
	{
		position.y--;
		if (animator->MotionEnd())
			animator->SetCurrentAnimation("Run_Up");
		direction = Direction::Up;
	}
	if (input_manager->GetKeyDown("MoveDown"))
	{
		position.y++;
		animator->SetCurrentAnimation("Idle_Down");
		direction = Direction::Down;
	}

	else if (input_manager->GetKeyPress("MoveDown"))
	{
		position.y++;
		if (animator->MotionEnd())
			animator->SetCurrentAnimation("Run_Down");
		direction = Direction::Down;
	}

	if (input_manager->GetKeyDown("MoveRight"))
	{
		position.x++;
		animator->SetCurrentAnimation("Idle_Right");
		direction = Direction::Right;
	}

	else if (input_manager->GetKeyPress("MoveRight"))
	{
		position.x++;
		if(animator->MotionEnd())
			animator->SetCurrentAnimation("Run_Right");
		direction = Direction::Right;
	}
	
	if (input_manager->GetKeyDown("MoveLeft"))
	{
		position.x--;
		animator->SetCurrentAnimation("Idle_Left");
		direction = Direction::Left;
	}

	else if (input_manager->GetKeyPress("MoveLeft"))
	{
		position.x--;
		if (animator->MotionEnd())
			animator->SetCurrentAnimation("Run_Left");
		direction = Direction::Left;
	}
	
	transform->SetPosition(position);
}

void MoveScriptComponent::Destroy()
{
}