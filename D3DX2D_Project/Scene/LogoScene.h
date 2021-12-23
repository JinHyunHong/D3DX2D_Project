#pragma once
#include "Scene.h"

class LogoScene final :
	public Scene
{
public:
	LogoScene(class Tool* const tool);
	~LogoScene();

	void Input() override;
	void Update() override;
	void Destroy() override;

private:
};