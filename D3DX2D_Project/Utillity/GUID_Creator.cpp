#include "stdafx.h"
#include "GUID_Creator.h"

auto GUID_Creator::CreateID() -> const uint
{
	std::hash<std::string> hasher;

	return hasher(CreateIDToString());
}

auto GUID_Creator::CreateIDToString() -> const std::string
{
	GUID guid;

	auto h_result = CoCreateGuid(&guid);
	assert(SUCCEEDED(h_result));

	std::stringstream sstream;

	sstream << std::hex << std::uppercase
		<< std::setw(8) << std::setfill('0') << guid.Data1 << "-"
		<< std::setw(4) << std::setfill('0') << guid.Data1 << "-"
		<< std::setw(4) << std::setfill('0') << guid.Data1 << "-"
		<< std::setw(2) << std::setfill('0') << guid.Data1 << "-"
		<< std::setw(2) << std::setfill('0') << static_cast<uint>(guid.Data4[0])
		<< std::setw(2) << std::setfill('0') << static_cast<uint>(guid.Data4[1])
		<< std::setw(2) << std::setfill('0') << static_cast<uint>(guid.Data4[2])
		<< std::setw(2) << std::setfill('0') << static_cast<uint>(guid.Data4[3])
		<< std::setw(2) << std::setfill('0') << static_cast<uint>(guid.Data4[4])
		<< std::setw(2) << std::setfill('0') << static_cast<uint>(guid.Data4[5])
		<< std::setw(2) << std::setfill('0') << static_cast<uint>(guid.Data4[6])
		<< std::setw(2) << std::setfill('0') << static_cast<uint>(guid.Data4[7]);


	return sstream.str();
}
