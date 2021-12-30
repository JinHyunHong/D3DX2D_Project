#pragma once
#include "Scene.h"

class MapEditorScene final :
	public Scene
{
public:
	MapEditorScene(class Tool* const tool);
	~MapEditorScene();

	void Initialize() override;
	void Input() override;
	void Update() override;
	void Destroy() override;

	void CreateTiles(const float& width, const float& height);

private:
	// 배경이 따로 있을 경우
	std::shared_ptr<class Actor> back_ground;
	float width = 0.0f;
	float height = 0.0f;
	float speed = 0.1f;

private:
	// 타일로만 배경을 만들 경우
	std::shared_ptr<class Layer> tile_layer;
	std::vector<class Actor> tiles;
};