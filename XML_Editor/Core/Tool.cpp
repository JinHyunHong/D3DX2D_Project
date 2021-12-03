#include "stdafx.h"
#include "Tool.h"

Tool::Tool()
{
}

Tool::~Tool()
{
}

bool Tool::Initialize()
{
	for (const auto& manager : managers)
		manager->Initialize();

	return true;
}


bool Tool::Update()
{
	for (const auto& manager : managers)
		manager->Update();

	return true;
}

void Tool::AddManager(const std::shared_ptr<class IManager>& manager)
{
	if (!manager)
	{
		assert(false);
		return;
	}

	managers.emplace_back(manager);
}
