#pragma once

class IManager
{
public:
	IManager() = default;
	virtual ~IManager() = default;

	virtual bool Initiailize() = 0;
	virtual void Update() = 0;
};