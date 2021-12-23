#pragma once
#include "Scene.h"

class NameSelectScene final :
	public Scene
{
public:
	NameSelectScene(class Tool* const tool);
	~NameSelectScene();

	void Initialize() override;
	void Input() override;
	void Update() override;
	void Destroy() override;

private:
	std::shared_ptr<class Actor> name_board = nullptr;
	std::shared_ptr<class Actor> name_board_small = nullptr;
	std::shared_ptr<class Actor> scope = nullptr;
	float frame_counter = 0.0f;
};