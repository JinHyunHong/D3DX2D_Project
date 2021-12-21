#pragma once

class Actor final
{
public:
	Actor(class Tool* const tool);
	~Actor();

	bool Initialize();
	void Update();
	void Destroy();

	auto GetName() const -> const std::string& { return name; }
	void SetName(const std::string& name) { this->name = name; }

	auto IsActive() { return is_active; }
	void SetActive(const bool& is_active) { this->is_active = is_active; }

	auto GetComponents() const -> const std::vector<std::shared_ptr<class IComponent>>& { return components; }
	
	template<typename T>
	auto GetComponent() const -> std::shared_ptr<T>;

	template<typename T>
	auto AddComponent() const->std::shared_ptr <T*>;

	template<typename T>
	bool EraseComponent();

	template<typename T>
	bool HasComponent();


private:
	Tool* tool = nullptr;
	std::string name = "";
	bool is_active = true;
	std::shared_ptr<class TransformComponent> transform;
	std::vector<std::shared_ptr<class IComponent>> components;
};

#include "Actor.inl"

