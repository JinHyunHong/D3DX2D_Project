#pragma once
#include "IManager.h"
#include "Resource/IResource.h"
#include <filesystem>

enum class AssetType : uint
{
	Texture,
	Shader,
	Animation
};

class ResourceManager final :
	public IManager
{
public:
	ResourceManager(class Tool* const tool);
	~ResourceManager() = default;

	bool Initialize() override;
	void Update() override {};

	template<typename T>
	auto Load(const std::string& path) -> const std::shared_ptr<T>;
	
	template<typename T>
	bool Load(const std::string& path, std::shared_ptr<T> resource);

	template<typename T>
	auto GetResourceFromName(const std::string& name) -> const std::shared_ptr<T>;

	template<typename T>
	auto GetResourceFromPath(const std::string& path) -> const std::shared_ptr<T>;

	template<typename T>
	auto RegisterResource(const std::shared_ptr<T>& resource);

	bool HasResource(const std::string& resource_name, const ResourceType& resource_type);

	auto GetAssetDirectory() const -> const std::string { return "../_Assert/"; }
	auto GetAssetDirectory(const AssetType& type) -> const std::string;

private:
	void RegisterDirectory(const AssetType& type, const std::string& directory);


private:
	using resource_group_t = std::vector <std::shared_ptr<IResource>>;
	std::map<ResourceType, resource_group_t> resource_groups;
	std::mutex resource_mutex;
	std::map<AssetType, std::string> asset_directories;
};

#include "ResourceManager.inl"