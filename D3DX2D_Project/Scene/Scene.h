#pragma once

class Scene
{
public:
	Scene(class Tool* const tool);
	virtual ~Scene();

	virtual void Input();
	virtual void Update();
	virtual void Destroy();

	auto CreateActor(bool is_active = true) -> std::shared_ptr<class Actor>;
	auto GetActors() const -> const std::vector<std::shared_ptr<class Actor>>& { return actors; }

protected:
	class Tool* tool = nullptr;
	class Timer* timer = nullptr;
	std::vector<std::shared_ptr<class Actor>> actors;
	class Renderer* renderer = nullptr;
	bool is_active = true;
	bool is_update = true;
};