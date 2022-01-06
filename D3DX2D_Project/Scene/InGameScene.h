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
	using layer_pointer = std::shared_ptr<class Layer>;
	using actor_pointer = std::shared_ptr<class Actor>;

private:
	layer_pointer hud_layer = nullptr;
	actor_pointer hud = nullptr;
	actor_pointer player = nullptr;
	float camera_pivot = 0.5f;
	std::vector<actor_pointer> hearts;
	bool is_open = false;

public:
	auto LoadTextureActor(const std::string& name, class Layer* const layer, 
		const std::string& path, const std::string& curent_texture_name, 
		const D3DXVECTOR3& scale, const D3DXVECTOR3& position) -> const actor_pointer;
};