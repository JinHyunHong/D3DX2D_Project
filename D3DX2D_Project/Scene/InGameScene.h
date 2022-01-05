#pragma once
#include "Scene.h"

class InGameScene final :
	public Scene
{
public:
	InGameScene(class Tool* const tool);
	~InGameScene();

	void Initialize() override;
	void Input() override;
	void Update() override;
	void Destroy() override;

private:
	using actor_pointer = std::shared_ptr<class Actor>;
	actor_pointer hud = nullptr;
	actor_pointer player = nullptr;
	float camera_pivot = 0.5f;

public:
	auto CreateHeart(const std::string& name, class Layer* const layer, 
		const D3DXVECTOR3& scale, const D3DXVECTOR3& position) -> const actor_pointer;
};