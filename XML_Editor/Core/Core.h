#pragma once
#include "../Header/Window.h"

class Core final
{
private:
	Core() = default;
	~Core() = default;

public:
	static Core& GetInst()
	{
		static Core Inst;
		return Inst;
	}

	auto GetClientWidth() const -> const float& { return width; }
	void SetClientWidth(const float& width) { this->width = width; }

	auto GetClientHegiht() const -> const float& { return height; }
	void SetClientHegiht(const float& height) { this->height = height; }

	auto GetWindowHandle() const -> const HWND& { return handle; }
	void SetWindowHandle(const HWND& handle) { this->handle = handle; }

	auto GetInstance() const -> const HINSTANCE& { return instance; }
	void SetInstance(const HINSTANCE& instance) { this->instance = instance; }


private:
	float width = 0.0f;
	float height = 0.0f;
	HWND handle = nullptr;
	HINSTANCE instance = nullptr;
};