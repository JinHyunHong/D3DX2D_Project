#include "stdafx.h"
#include "IComponent.h"
#include "TransformComponent.h"

IComponent::IComponent(Tool* const tool, Actor* const actor, TransformComponent* const transform)
	: tool(tool), actor(actor), transform(transform)
{
}
