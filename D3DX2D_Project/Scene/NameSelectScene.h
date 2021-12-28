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
	std::shared_ptr<class Layer> board_layer = nullptr;
	std::shared_ptr<class Actor> select = nullptr;
	std::shared_ptr<class Actor> scope = nullptr;
	std::string player_name = " ";
	const uint name_size = 8;
	float frame_counter = 0.0f;
};