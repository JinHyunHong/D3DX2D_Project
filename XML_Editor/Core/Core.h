#pragma once

class Core final
{
public:
	static Core& GetInst()
	{
		static Core Inst;
		return Inst;
	}

private:
	Core();
	~Core();

public:
	const bool Initalize(const HINSTANCE& instance, const uint& width, const uint& height);
	const bool Update();

public:
	auto GetClientWidth() const -> const uint& { return width; }
	void SetClientWidth(const uint& width) { this->width = width; }

	auto GetClientHegiht() const -> const uint& { return height; }
	void SetClientHegiht(const uint& height) { this->height = height; }

	auto GetWindowHandle() const -> const HWND& { return handle; }
	void SetWindowHandle(const HWND& handle) { this->handle = handle; }

	auto GetInstance() const -> const HINSTANCE& { return instance; }
	void SetInstance(const HINSTANCE& instance) { this->instance = instance; }


public:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
	const bool Create();
	void Show();
	void Destroy();

private:
	uint width = 0;
	uint height = 0;
	HWND handle = nullptr;
	HINSTANCE instance = nullptr;
};