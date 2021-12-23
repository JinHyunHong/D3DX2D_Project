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

	template<typename T>
	auto CreateScene(const std::string& scene_name) -> std::shared_ptr<T>;

	auto GetAllScene() const -> const std::unordered_map<std::string, std::shared_ptr<class Scene>>& { return scenes; }

private:
	std::weak_ptr<class Scene> current_scene;
	std::unordered_map<std::string, std::shared_ptr<class Scene>> scenes;
};

template<typename T>
inline auto SceneManager::CreateScene(const std::string& scene_name) -> std::shared_ptr<T>
{
	static_assert(std::is_base_of<Scene, T>::value, "Type T is not a derived class of Scene");

	if (scenes.find(scene_name) != scenes.end())
	{
		assert(false);
		return nullptr;
	}

	auto new_scene = std::make_shared<T>(tool);

	scenes[scene_name] = new_scene;

	return new_scene;	
}
