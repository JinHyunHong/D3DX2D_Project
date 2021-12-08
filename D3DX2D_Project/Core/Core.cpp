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

	tool = new Tool();

	tool->AddManager(std::make_shared<SubsystemManager>(tool));
	auto sub_manager = tool->GetManager<SubsystemManager>();
	tool->Initialize();

	current_window = std::make_shared<window>(tool, instance, width, height);
	current_window->Create(L"D3DX2D_Project", L"D3DX2D_Project");
	current_window->Show();

	return true;
}

bool Core::Update()
{
	if (!current_window->Update())
		return false;
	tool->Update();
	return true;
}

void Core::Destroy()
{
	current_window->Destroy();
	delete tool;
	tool = nullptr;
}