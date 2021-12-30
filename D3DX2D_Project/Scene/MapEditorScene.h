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

private:
	// ����� ���� ���� ���
	std::shared_ptr<class Actor> back_ground;
	float width = 0.0f;
	float height = 0.0f;

private:
	// Ÿ�Ϸθ� ����� ���� ���
	std::vector<class Tile> tiles;
};