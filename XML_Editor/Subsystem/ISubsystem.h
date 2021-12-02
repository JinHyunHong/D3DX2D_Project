#pragma once

class ISubsystem
{
public:
	ISubsystem() = default;
	virtual ~ISubsystem() = default;

	virtual bool Initailize() = 0;
	virtual bool Update() = 0;

private:
};