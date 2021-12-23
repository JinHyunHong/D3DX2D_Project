#pragma once
#include "Scene.h"

class MenuScene final :
	public Scene
{
public:
	MenuScene(class Tool* const tool);
	~MenuScene();

	void Input() override;
	void Update() override;
	void Destroy() override;

private:
	std::shared_ptr<class Actor> move_mouse;
	float frame_counter = 0.0f;
	const int SLOT_NUM = 5;
	int slot_index = 0;
};