#pragma once
#include "IRendererComponent.h"

class MeshRendererComponent :
	public IRendererComponent
{
public:
	MeshRendererComponent(class Tool* const tool, class Actor* const actor,
		class TransformComponent* const transform);
	~MeshRendererComponent() = default;

	bool Initialize() override;
	void Update() override;
	void Destroy() override;
};