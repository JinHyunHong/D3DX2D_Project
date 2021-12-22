#pragma once

class SceneManager final :
	public ISubsystem
{
public:
	SceneManager(class Tool* const tool);
	~SceneManager();

	bool Initialize() override;
	void Update() override;
	void Destroy() override;

	auto GetCurrentScene_Raw() -> class Scene* const;
	auto GetCurrentScene() const -> std::shared_ptr<class Scene>;

	void SetCurrentScene(const std::string& scene_name);

	auto CreateScene(const std::string& scene_name) -> std::shared_ptr<class Scene>;

	auto GetAllScene() const -> const std::unordered_map<std::string, std::shared_ptr<class Scene>>& { return scenes; }

private:
	std::weak_ptr<class Scene> current_scene;
	std::unordered_map<std::string, std::shared_ptr<class Scene>> scenes;
};