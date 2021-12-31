#include "stdafx.h"
#include "InputManager.h"

InputManager::InputManager(Tool* const tool) :
	ISubsystem(tool)
{
}

InputManager::~InputManager()
{
}

bool InputManager::Initialize()
{
	CreateKey("MoveUp", 'W');
	CreateKey("MoveDown", 'S');
	CreateKey("MoveLeft", 'A');
	CreateKey("MoveRight", 'D');
	CreateKey("Num1", '1');
	CreateKey("Num2", '2');
	CreateKey("Num3", '3');
	CreateKey("Num4", '4');
	CreateKey("LButton", VK_LBUTTON);
	return true;
}

void InputManager::Update()
{
	for (auto iter = event_keys.begin(); iter != event_keys.end(); ++iter)
	{
		int key_count = 0;
		for (uint i = 0; i < iter->second->keys.size(); ++i)
		{
			if (GetAsyncKeyState(iter->second->keys[i]) && 0x8000)
			{
				++key_count;
			}
		}

		if (key_count == iter->second->keys.size())
		{
			if (!iter->second->is_down && !iter->second->is_press)
			{
				iter->second->is_down = true;
				iter->second->is_press = true;
			}

			else if (iter->second->is_down)
			{
				iter->second->is_down = false;
			}
		}

		else
		{
			if (iter->second->is_down || iter->second->is_press)
			{
				iter->second->is_down = false;
				iter->second->is_press = false;
				iter->second->is_up = true;
			}

			else if (iter->second->is_up)
			{
				iter->second->is_down = false;
				iter->second->is_press = false;
				iter->second->is_up = false;
			}
		}
	}
}

void InputManager::Destroy()
{
}

auto InputManager::FindKey(const std::string& name) -> const std::shared_ptr<KeyInfo>
{
	assert(event_keys.find(name) != event_keys.end());

	for (auto iter = event_keys.begin(); iter != event_keys.end(); ++iter)
	{
		if ((*iter).first == name)
			return (*iter).second;
	}

	return nullptr;
}
