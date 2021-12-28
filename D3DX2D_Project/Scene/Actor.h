#pragma once
#include "Component/IComponent.h"

class Actor final
{
public:
	Actor(class Tool* const tool);
	~Actor();

	bool Initialize();
	void Update(const std::shared_ptr<Actor>& dest = nullptr);
	void Destroy();

	auto GetName() const -> const std::string& { return name; }
	void SetName(const std::string& name) { this->name = name; }

	auto IsUpdate() { return is_update; }
	void SetUpdate(const bool& is_update) { this->is_update = is_update; }

	auto IsActive() { return is_active; }
	void SetActive(const bool& is_active) { this->is_active = is_active; }

	auto GetComponents() const -> const std::vector<std::shared_ptr<class IComponent>>& { return components; }
	
	template<typename T>
	auto GetComponent() -> const std::shared_ptr<T>;

	template<typename T>
	auto AddComponent() -> const std::shared_ptr<T>;

	template<typename T>
	bool EraseComponent();

	template<typename T>
	bool HasComponent();


private:
	Tool* tool = nullptr;
	std::string name = "";
	bool is_active = true;
	bool is_update = true;
	std::shared_ptr<class TransformComponent> transform;
	std::vector<std::shared_ptr<class ColliderComponent>> colliders;
	std::vector<std::shared_ptr<class IComponent>> components;
}; 

template<typename T>
inline auto Actor::GetComponent() -> const std::shared_ptr<T>
{
	static_assert(std::is_base_of<IComponent, T>::value, "Type T is not a derived class of IComponent");

	for (const auto& component : components)
	{
		if (typeid(*component) == typeid(T))
			return std::static_pointer_cast<T>(component);
	}

	return nullptr;
}

template<typename T>
inline auto Actor::AddComponent() -> const std::shared_ptr<T>
{
	static_assert(std::is_base_of<IComponent, T>::value, "Type T is not a derived class of IComponent");

	if (HasComponent<T>())
		return GetComponent<T>();

	components.emplace_back
	(
		std::make_shared<T>
		(
			tool,
			this,
			transform.get()
		)
	);

	auto new_component = std::static_pointer_cast<T>(components.back());


	if (!new_component.get()->Initialize())
	{
		assert(false);
		return nullptr;
	}

	if constexpr (std::is_same<T, class TransformComponent>::value)
		transform = new_component;

	if constexpr (std::is_same<T, class ColliderComponent>::value)
		colliders.push_back(new_component);

	return new_component;
}

template<typename T>
inline bool Actor::EraseComponent()
{
	static_assert(std::is_base_of<IComponent, T>::value, "Type T is not a derived class of IComponent");

	for (auto begin = components.begin(); begin != components.end(); ++begin)
	{
		auto component = (*begin);
		if (typeid(component) == typeid(T))
		{
			component.get()->Destroy();
			component.reset();
			components.erase(begin);
			return true;
		}
	}

	return false;
}

template<typename T>
inline bool Actor::HasComponent()
{
	static_assert(std::is_base_of<IComponent, T>::value, "Type T is not a derived class of IComponent");

	for (const auto& component : components)
	{
		if (typeid(*component) == typeid(T))
			return true;
	}

	return false;
}


#include "Actor.inl"

