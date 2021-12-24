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
};