#pragma once

class ISubsystem
{
public:
	ISubsystem(class Tool* const tool);
	virtual ~ISubsystem() = default;

	virtual bool Initialize() = 0;
	virtual void Update() = 0;
	virtual void Destroy() = 0;

protected:
	class Tool* tool = nullptr;
};