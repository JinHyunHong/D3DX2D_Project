#pragma once
#include "stdafx.h"

class Object
{
public:
	Object() { id = GUID_Creator::CreateID(); }
	virtual ~Object() = default;

	auto GetID() const { return id; }
	void SetID(const uint& id) { this->id = id; }

private:
	uint id = 0;
};