#pragma once

class GUID_Creator final
{
public:
	GUID_Creator() = default;
	~GUID_Creator() = default;

	static auto CreateID() -> const uint;
	static auto CreateIDToString() -> const std::string;
};