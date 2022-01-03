#include "stdafx.h"
#include "Layer.h"
#include "Scene/Actor.h"
#include "Scene/Component/TransformComponent.h"
#include "Scene/Component/ColliderComponent.h"


Layer::Layer(class Tool* const tool) :
	tool(tool)
{
}

Layer::~Layer()
{
	EraseActors();
}

bool Layer::Initialize()
{
	return true;
}

void Layer::Update(class Renderer* renderer)
{
	if (!is_active)
		return;

	for (auto iter = actors.begin(); iter != actors.end(); ++iter)
	{
		if (auto collider = (*iter)->GetComponent<ColliderComponent>())
			collider->Destroy();
	}

	for (auto iter = actors.begin(); iter != actors.end(); ++iter)
	{
		if (offset_position != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		{
			if (!(*iter)->IsUpdate())
				continue;
			auto transform = (*iter)->GetComponent<TransformComponent>();
			transform->SetPosition(transform->GetPosition() + offset_position);
		}
		
		for (auto iter1 = iter; iter1 != actors.end();)
		{
			if (iter1 + 1 == actors.end())
			{
				(*iter)->Update();
				iter1++;
				break;
			}

			iter1++;
			(*iter)->Update((*iter1));
		}
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

auto Layer::GetActor(const uint& index) -> std::shared_ptr<class Actor>
{
	if (index < 0 || index > actors.size())
	{
		return nullptr;
	}

	return actors[index];
}

void Layer::EraseActors()
{
	for (auto iter = actors.begin(); iter != actors.end();)
	{
		(*iter).reset();
		iter = actors.erase(iter);
	}

	CLEAR_VECTOR(actors);
}

bool Layer::EraseActor(const std::string& name)
{
	for (auto iter = actors.begin(); iter != actors.end(); ++iter)
	{
		if ((*iter)->GetName() == name)
		{
			(*iter).reset();
			actors.erase(iter);
			return true;
		}
	}

	return false;
}
