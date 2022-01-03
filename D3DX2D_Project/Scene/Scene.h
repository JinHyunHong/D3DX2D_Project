#pragma once

class Scene
{
public:
	Scene(class Tool* const tool);
	virtual ~Scene() = 0;

	virtual void Initialize();
	virtual void Input();
	virtual void Update();
	virtual void Destroy();

	auto CreateLayer(const std::string& name, bool is_active = true)->std::shared_ptr<class Layer>;
	auto GetLayers() const -> const std::vector<std::shared_ptr<class Layer>>& { return layers; }	
	
	void CreateBackground(const std::vector<std::string>& animation_paths, 
		const std::string& current_animation, const D3DXVECTOR3& scale, 
		const D3DXVECTOR3& position, Xml::XMLElement* sibling_element);
	void CreateTiles(const std::string& path, Xml::XMLElement* first_element, 
		const float& width, const float& height);

	auto GetTileIndex(const D3DXVECTOR2& position) const -> const uint;

	bool SaveToFile(const std::string& path);
	bool LoadFromFile(const std::string& path, const std::string& current_animation, const bool& is_background = false);

protected:
	class Tool* tool = nullptr;
	class Timer* timer = nullptr;
	class D3D11_Base* graphics = nullptr;
	std::vector<std::shared_ptr<class Layer>> layers;
	std::shared_ptr<class Actor> camera;
	class Renderer* renderer = nullptr;
	bool is_active = true;


	// 배경을 위한 것
protected:
	// 배경이 따로 있을 경우
	std::shared_ptr<class Actor> back_ground;
	// 타일로만 배경을 만들 경우
	std::shared_ptr<class Layer> tile_layer;
	std::shared_ptr<class Layer> back_ground_layer;
	float width = 0.0f;
	float height = 0.0f;
	float speed = 0.1f;
	float window_width = 0.0f;
	float window_height = 0.0f;
	D3DXVECTOR2 tile_size = D3DXVECTOR2(50.0f, 50.0f);
	uint tile_number_x = 0;
	uint tile_number_y = 0;
};