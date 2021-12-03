#pragma once
#include "IManager.h"
#include "Subsystem/ISubsystem.h"

class SubsystemManager final :
	public IManager
{
public:
	SubsystemManager();
	~SubsystemManager();

	bool Initiailize() override;
	void Update() override;

	template<typename T>
	auto GetSubsystem() const -> const std::shared_ptr<class ISubsystem>;

	auto GetSubsystems() const -> const std::vector<std::shared_ptr<class ISubsystem>>& { return subsystems; }

private:
	std::vector<std::shared_ptr<class ISubsystem>> subsystems;
};

template<typename T>
inline auto SubsystemManager::GetSubsystem() const -> const std::shared_ptr<class ISubsystem>
{
	static_assert(std::is_base_of<ISubsystem, T>::value, "Type T has no is-a relationship with ISubsystem.");
	
	for (const auto& subsystem : subsystems)
	{
		if (typeid(*subsystem) == typeid(T))
			return subsystem;
	}
	
	return nullptr;
}
