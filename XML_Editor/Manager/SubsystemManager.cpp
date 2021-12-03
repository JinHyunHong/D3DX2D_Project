#include "stdafx.h"
#include "SubsystemManager.h"


SubsystemManager::SubsystemManager(class Tool* const tool) :
	IManager(tool)
{
}

SubsystemManager::~SubsystemManager()
{
}

bool SubsystemManager::Initialize()
{
	for (const auto& subsystem : subsystems)
	{
		if (!subsystem->Initialize())
		{
			assert(false);
			return false;
		}
	}
	
	return true;
}

void SubsystemManager::Update()
{
	for (const auto& subsystem : subsystems)
		subsystem->Update();
}

void SubsystemManager::AddSubsystem(const std::shared_ptr<ISubsystem>& subsystem)
{
	if (!subsystem)
	{
		assert(false);
		return;
	}

	subsystems.emplace_back(subsystem);
}

