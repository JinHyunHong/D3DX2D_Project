#pragma once
#include "IManager.h"
#include "Subsystem/ISubsystem.h"

class SubsystemManager final :
	public IManager
{
public:
	SubsystemManager(class Tool* const tool);
	~SubsystemManager();

	bool Initialize() override;
	void Update() override;

	void AddSubsystem(const std::shared_ptr<class ISubsystem>& subsystem);

	template<typename T>
	auto GetSubsystem() const -> std::shared_ptr<T>;

	template<typename T>
	auto GetSubsystem_raw() const -> T*;

	auto GetSubsystems() const -> const std::vector<std::shared_ptr<class ISubsystem>>& { return subsystems; }

private:
	std::vector<std::shared_ptr<class ISubsystem>> subsystems;
};

template<typename T>
inline auto SubsystemManager::GetSubsystem() const-> std::shared_ptr<T>
{
	static_assert(std::is_base_of<ISubsystem, T>::value, "Type T has no is-a relationship with ISubsystem.");
	
	for (const auto& subsystem : subsystems)
	{
		if (typeid(*subsystem) == typeid(T))
			return std::static_pointer_cast<T>(subsystem);
	}
	
	return nullptr;
}

template<typename T>
inline auto SubsystemManager::GetSubsystem_raw() const -> T*
{
	static_assert(std::is_base_of<ISubsystem, T>::value, "Type T has no is-a relationship with ISubsystem.");

	for (const auto& subsystem : subsystems)
	{
		if (typeid(*subsystem) == typeid(T))
			return std::static_pointer_cast<T>(subsystem).get();
	}

	return nullptr;
}
