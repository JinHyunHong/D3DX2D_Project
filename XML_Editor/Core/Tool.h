#pragma once
#include "Manager/IManager.h"

class Tool final
{
public:
	Tool();
	~Tool();

	bool Initialize();
	bool Update();

	template<typename T>
	auto GetManager() const -> const std::shared_ptr<T>;

	auto GetManagers() const -> const std::vector<std::shared_ptr<class IManager>>& { return managers; }

	void AddManager(const std::shared_ptr<class IManager>& manager);

private:
	std::vector<std::shared_ptr<class IManager>> managers;
};

template<typename T>
inline auto Tool::GetManager() const -> const std::shared_ptr<T>
{
	static_assert(std::is_base_of<IManager, T>::value, "Type T has no is-a relationship with IManager.");

	for (const auto& manager : managers)
	{
		if (typeid(*manager) == typeid(T))
			return std::static_pointer_cast<T>(manager);
	}

	return nullptr;
}