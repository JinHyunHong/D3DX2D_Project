#pragma once
#include "IComponent.h"

class AIScriptComponent final :
	public IComponent
{
public:
	AIScriptComponent(class Tool* const tool, class Actor* const actor,
		class TransformComponent* const transform);
	~AIScriptComponent() = default;

	bool Initialize() override;
	void Update() override;
	void Destroy() override;

private:
	Stopwatch stopwatch;
	Direction direction = Direction::Left;
};
