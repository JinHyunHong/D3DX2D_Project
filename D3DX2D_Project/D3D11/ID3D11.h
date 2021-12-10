#pragma once

class ID3D11
{
public:
	ID3D11() { id = GUID_Creator::CreateID(); }
	virtual ~ID3D11() = default;

	auto GetID() const { return id; }
	void SetID(const uint& id) { this->id = id; }

private:
	uint id = 0;
};