#include "stdafx.h"
#include "Core.h"
#include "Manager/PathManager.h"
#include "Manager/SubsystemManager.h"
#include "Subsystem/Context.h"

Core::~Core()
{
	delete tool;
	tool = nullptr;
}

bool Core::Initialize(HINSTANCE instance, const uint& width, const uint& height)
{
	this->instance = instance;
	this->width = width;
	this->height = height;

	AddWindow(WindowSplitType::Main);
	AddWindow(WindowSplitType::Left);
	AddWindow(WindowSplitType::Right);

	tool = new Tool();
	tool->Initialize();
	tool->AddManager(std::make_shared<PathManager>(tool));
	tool->AddManager(std::make_shared<SubsystemManager>(tool));
	auto sub_manager = tool->GetManager<SubsystemManager>();
	sub_manager->AddSubsystem(std::make_shared<Context>(tool));

	return true;
}

bool Core::Update()
{
	for (const auto& window : windows)
		if (!window->Update())
			return false;

	tool->Update();
	return true;
}

void Core::Destroy()
{
	for (const auto& window : windows)
		window->Destroy();
}

auto Core::AddWindow(const WindowSplitType& type) -> const std::shared_ptr<window>
{
	auto screen = GetWindow(type);

	if (screen)
		return screen;

	screen = std::make_shared<window>(type, instance, width, height);
	switch (type)
	{
	case WindowSplitType::Unknown:
	{
		assert(false);
		return nullptr;
	}
	case WindowSplitType::Left:
	{
		screen->SetParent(GetWindow(WindowSplitType::Main));
		break;
	}
	case WindowSplitType::Right:
	{
		screen->SetParent(GetWindow(WindowSplitType::Main));
		break;
	}

	case WindowSplitType::Main:
	default:
		break;
	}

	screen->Create();
	screen->Show();

	windows.emplace_back(screen);
	return screen;
}

auto Core::GetWindow(const WindowSplitType& type) const -> const std::shared_ptr<window>
{
	for (const auto& window : windows)
	{
		if (window->GetType() == type)
			return window;
	}

	return nullptr;
}
