#include "stdafx.h"
#include "PathManager.h"

PathManager::PathManager()
{
}

bool PathManager::Initiailize()
{
	std::filesystem::path root_path_name = std::filesystem::current_path();
	root_path = root_path_name.string();

	CreatePath(Directory_path::XmlFiles, root_path + "/XmlFiles");

	return true;
}

auto PathManager::GetPath(const Directory_path& type) -> const std::string
{
	if (directories.find(type) == directories.end())
		return "";

	return directories[type];
}

bool PathManager::CreatePath(const Directory_path& type, const std::string& path)
{
	if (directories.find(type) != directories.end())
		return false;

	directories[type] = path;
	return true;
}
