#pragma once

class Layer final
{
public:
	Layer(class Tool* const tool);
	~Layer();

	bool Initialize();
	void Update(class Renderer* renderer);
	void Destroy();

	auto CreateActor(bool is_active = true)->std::shared_ptr<class Actor>;
	auto GetActors() const -> const std::vector<std::shared_ptr<class Actor>>& { return actors; }

	auto IsActive() const { return is_active; }
	void SetActive(const bool& is_active) { this->is_active = is_active; }

	auto IsUpdate() const { return is_update; }
	void SetUpdate(const bool& is_update) { this->is_update = is_update; }

	auto GetName() const -> const std::string& { return name; }
	void SetName(const std::string& name) { this->name = name; }

	void SetOffsetPosition(const D3DXVECTOR3& offset) { this->offset_position = offset; }
	void SetOffsetPosition(const float& x, const float& y, const float& z) { this->offset_position = D3DXVECTOR3(x, y, z); }

private:
	class Tool* tool = nullptr;
	std::string name = "";
	D3DXVECTOR3 offset_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	std::vector<std::shared_ptr<class Actor>> actors;
	bool is_update = true;
	bool is_active = true;
};