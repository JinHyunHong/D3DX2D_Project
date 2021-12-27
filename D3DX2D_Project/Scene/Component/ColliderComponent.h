#pragma once
#include "IComponent.h"

class ColliderComponent :
	public IComponent
{
public:
	ColliderComponent(class Tool* const tool, class Actor* const actor,
		class TransformComponent* const transform);
	~ColliderComponent() = default;

	bool Initialize() override;
	void Update() override;
	void Destroy() override;

	bool IsCollision(class Actor* const src, class Actor* const dest);
};