#include "stdafx.h"
#include "SubsystemManager.h"


SubsystemManager::SubsystemManager()
{
}

SubsystemManager::~SubsystemManager()
{
}

bool SubsystemManager::Initiailize()
{
	for (const auto& subsystem : subsystems)
	{
		if (!subsystem->Initiailize())
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

