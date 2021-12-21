#include "Actor.h"

template<typename T>
inline auto Actor::GetComponent() const -> std::shared_ptr<T>
{
	static_assert(std::is_base_of<IComponent, T>::value, "Type T is not a derived class of IComponent");

	for (const auto& component : components)
	{
		if (typeid(*component) == typeid(T))
			return component;
	}

	return nullptr;
}

template<typename T>
inline auto Actor::AddComponent() const -> std::shared_ptr<T*>
{
	static_assert(std::is_base_of<IComponent, T>::value, "Type T is not a derived class of IComponent");

	auto new_component = std::make_shared<T>(tool);

	if (!new_component->Initialize())
	{
		assert(false);
		return nullptr;
	}

	components.emplace_back(new_component);

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
