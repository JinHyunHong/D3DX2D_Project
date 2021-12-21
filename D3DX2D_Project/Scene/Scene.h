#pragma once

class Scene final
{
public:
	Scene(class Tool* const tool);
	~Scene();

	void Update();

	auto CreateActor(bool is_active = true) -> std::shared_ptr<class Actor>;
	auto GetActors() const -> const std::vector<std::shared_ptr<class Actor>>& { return actors; }

private:
	class Tool* tool = nullptr;
	std::vector<std::shared_ptr<class Actor>> actors;
	class Renderer* renderer = nullptr;
	bool is_active = true;
};