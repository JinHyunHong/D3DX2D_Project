#pragma once
#include "Scene.h"

enum class Edit_Mode : uint
{
	NoMove,
	Move
};

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
	auto GetTileIndex(const D3DXVECTOR2& position) const -> const uint;

private:
	// ����� ���� ���� ���
	std::shared_ptr<class Actor> back_ground;
	// Ÿ�Ϸθ� ����� ���� ���
	std::shared_ptr<class Layer> tile_layer;
	Edit_Mode edit_mode = Edit_Mode::NoMove;
	float width = 0.0f;
	float height = 0.0f;
	float speed = 0.1f;
	float window_width = 0.0f;
	float window_height = 0.0f;
	uint tile_number_x = 0;
	uint tile_number_y = 0;

private:
	float frame_counter = 0.0f;
};