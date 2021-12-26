#include "stdafx.h"
#include "Layer.h"
#include "Scene/Actor.h"
#include "Scene/Component/TransformComponent.h"


Layer::Layer(class Tool* const tool) :
	tool(tool)
{
}

Layer::~Layer()
{
	CLEAR_VECTOR(actors);
}

bool Layer::Initialize()
{
	return true;
}

void Layer::Update(class Renderer* renderer)
{
	if (!is_active)
		return;

	for (const auto& actor : actors)
	{
		if (offset_position != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		{
			auto transform = actor->GetComponent<TransformComponent>();
			transform->SetPosition(transform->GetPosition() + offset_position);
		}
		
		actor->Update();
	}

	if (is_update)
	{
		renderer->UpdateRenderables(this);
		is_update = false;
	}

	offset_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

void Layer::Destroy()
{
}

auto Layer::CreateActor(bool is_active) -> std::shared_ptr<class Actor>
{
	auto new_actor = std::make_shared<Actor>(tool);

	if (!new_actor->Initialize())
	{
		assert(false);
		return nullptr;
	}

	new_actor->SetActive(is_active);

	return actors.emplace_back(new_actor);
}
