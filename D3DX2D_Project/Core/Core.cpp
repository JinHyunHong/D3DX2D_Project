#include "stdafx.h"
#include "Core.h"

Core::~Core()
{
	Destroy();
}

bool Core::Initialize(HINSTANCE instance, const uint& width, const uint& height)
{
	this->instance = instance;
	this->width = width;
	this->height = height;


	// Create Window
	current_window = std::make_shared<window>(tool, instance, width, height);
	current_window->Create(L"D3DX2D_Project", L"D3DX2D_Project");
	current_window->Show();

	tool = new Tool();

	// Managers Initialize
	tool->AddManager(std::make_shared<ResourceManager>(tool));

	auto sub_manager = std::make_shared<SubsystemManager>(tool);
	tool->AddManager(sub_manager);

	// Subsystem Create
	sub_manager->AddSubsystem(std::make_shared<Timer>(tool));
	sub_manager->AddSubsystem(std::make_shared<InputManager>(tool));
	sub_manager->AddSubsystem(std::make_shared<D3D11_Base>(tool));
	sub_manager->AddSubsystem(std::make_shared<Renderer>(tool));
	sub_manager->AddSubsystem(std::make_shared<SceneManager>(tool));

	if (!tool->Initialize())
	{
		assert(false);
		return false;
	}

	return true;
}

bool Core::Update()
{
	if (!current_window->Update())
		return false;
	tool->Update();
	return true;
}

void Core::Render()
{
	Renderer* renderer = tool->GetManager<SubsystemManager>()->GetSubsystem<Renderer>();
	renderer->Update();
}

void Core::Destroy()
{
	current_window->Destroy();
	delete tool;
	tool = nullptr;
}