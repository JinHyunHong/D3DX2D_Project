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
	sub_manager->AddSubsystem(std::make_shared<Context>(tool));
	tool->Initialize();

	current_window = std::make_shared<window>(tool, instance, width, height);
	current_window->Create(L"XML_Editor", L"제목없음");
	current_window->Show();


	Context* context = sub_manager->GetSubsystem_raw<Context>();
	current_window->DrawTextWindow(context->ToString());

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