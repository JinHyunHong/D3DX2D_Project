#pragma once
#include "IComponent.h"

class MoveScriptComponent final
	: public IComponent
{
public:
	MoveScriptComponent(class Tool* const tool, class Actor* const actor,
		class TransformComponent* const transform);
	~MoveScriptComponent() = default;

	bool Initialize() override;
	void Update() override;
	void Destroy() override;

	auto GetDirection() const -> const Direction& { return direction; }

private:
	Direction direction = Direction::Down;
	float speed = 0.04f;
};

