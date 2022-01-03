#include "stdafx.h"
#include "MeshRendererComponent.h"

MeshRendererComponent::MeshRendererComponent(Tool* const tool, Actor* const actor, TransformComponent* const transform) :
	IRendererComponent(tool, actor, transform)
{
}

bool MeshRendererComponent::Initialize()
{
	IRendererComponent::Initialize();

	return true;
}

void MeshRendererComponent::Update()
{
}

void MeshRendererComponent::Destroy()
{
}