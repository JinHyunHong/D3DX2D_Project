#pragma once
#include "IManager.h"

enum class Directory_path
{
	XmlFiles
};

class PathManager final :
	public IManager
{
public:
	PathManager(class Tool* const tool);
	~PathManager() = default;

	bool Initialize() override;
	void Update() override {};

	auto GetRootPath() const -> const std::string& { return root_path; }
	auto GetPath(const Directory_path& type) -> const std::string;

	bool CreatePath(const Directory_path& type, const std::string& path);

private:
	std::string root_path;
	std::unordered_map<Directory_path, std::string> directories;
};