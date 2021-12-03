#pragma once

class IManager
{
public:
	IManager(class Tool* const tool);
	virtual ~IManager() = default;

	virtual bool Initialize() = 0;
	virtual void Update() = 0;

protected:
	class Tool* tool = nullptr;
};