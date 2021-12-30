#pragma once
#include "ISubsystem.h"

struct KeyInfo final
{
	std::string name = "";
	std::vector<DWORD> keys;
	bool is_down = false;
	bool is_press = false;
	bool is_up = false;
};

class InputManager final :
	public ISubsystem
{
public:
	InputManager(class Tool* const tool);
	~InputManager();

	bool Initialize();
	void Update();
	void Destroy();


	template<typename T>
	bool CreateKey(const T& data);

	template<typename T, typename ... Types>
	bool CreateKey(const T& data, const Types&... arg);

	auto FindKey(const std::string& name) -> const std::shared_ptr<KeyInfo>;

	auto GetKeyDown(const std::string& name) -> const bool& { return FindKey(name)->is_down; }
	auto GetKeyPress(const std::string& name) -> const bool& { return FindKey(name)->is_press; }
	auto GetKeyUp(const std::string& name) -> const bool& { return FindKey(name)->is_up; }

private:
	std::unordered_map<std::string, std::shared_ptr<KeyInfo>> event_keys;
	std::shared_ptr<KeyInfo> key_info;
};

template<typename T>
inline bool InputManager::CreateKey(const T& data)
{
	if (!key_info)
	{
		key_info = std::make_shared<KeyInfo>();
	}

	if (strcmp(typeid(T).name(), "int") == 0 ||
		strcmp(typeid(T).name(), "char") == 0)
	{
		key_info->keys.push_back((DWORD)data);
	}

	else
	{
		key_info->name = data;
		event_keys[key_info->name] = key_info;
	}

	if (key_info)
	{
		key_info = nullptr;
	}

	return true;
}

template<typename T, typename ...Types>
inline bool InputManager::CreateKey(const T& data, const Types & ...arg)
{
	if (!key_info)
	{
		key_info = std::make_shared<KeyInfo>();
	}

	if (strcmp(typeid(T).name(), "int") == 0 ||
		strcmp(typeid(T).name(), "char") == 0)
	{
		key_info->keys.push_back((DWORD)data);
	}

	else
	{
		key_info->name = data;
		event_keys[key_info->name] = key_info;
	}

	CreateKey(arg...);

	if (key_info)
	{
		key_info = nullptr;
	}


	return true;
}
