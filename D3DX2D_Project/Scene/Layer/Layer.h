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

	auto GetName() const -> const std::string& { return name; }
	void SetName(const std::string& name) { this->name = name; }

private:
	class Tool* tool = nullptr;
	std::vector<std::shared_ptr<class Actor>> actors;
	std::string name = "";
	bool is_update = true;
	bool is_active = true;
};