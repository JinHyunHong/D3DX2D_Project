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
	std::shared_ptr<class Actor> hud = nullptr;
	std::shared_ptr<class Actor> player = nullptr;
	float camera_pivot = 0.5f;
	D3DXVECTOR3 prev_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
};