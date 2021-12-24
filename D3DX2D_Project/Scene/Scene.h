#pragma once

class Scene
{
public:
	Scene(class Tool* const tool);
	virtual ~Scene();

	virtual void Initialize();
	virtual void Input();
	virtual void Update();
	virtual void Destroy();

	auto CreateLayer(const std::string& name, bool is_active = true)->std::shared_ptr<class Layer>;
	auto GetLayers() const -> const std::vector<std::shared_ptr<class Layer>>& { return layers; }

protected:
	class Tool* tool = nullptr;
	class Timer* timer = nullptr;
	class D3D11_Base* graphics = nullptr;
	std::vector<std::shared_ptr<class Layer>> layers;
	class Renderer* renderer = nullptr;
	bool is_active = true;
};