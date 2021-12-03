#pragma once

class ISubsystem
{
public:
	ISubsystem() = default;
	virtual ~ISubsystem() = default;

	virtual bool Initiailize() = 0;
	virtual void Update() = 0;
};