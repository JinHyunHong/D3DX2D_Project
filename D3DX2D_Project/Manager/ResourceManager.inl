#include "ResourceManager.h"

template<typename T>
inline auto ResourceManager::Load(const std::string& path) -> const std::shared_ptr<T>
{
	static_assert(std::is_base_of<IResource, T>::value, "Provided type does not implement IResource");

	if (!std::filesystem::exists(path))
	{
		assert(false);
		return nullptr;
	}

	auto last_index = path.find_last_of("\\/");
	auto file_name = path.substr(last_index + 1, path.length());
	last_index = file_name.find_last_of(".");
	auto resource_name = file_name.substr(0, last_index);

	if (HasResource(resource_name, IResource::DeduceResourceType<T>()))
		return GetResourceFromName<T>(resource_name);

	auto resource = std::make_shared<T>(tool);
	resource->SetResourceName(resource_name);
	resource->SetResourcePath(path);

	if (!resource->LoadFromFile(path))
	{
		assert(false);
		return nullptr;
	}

	RegisterResource<T>(resource);

	return resource;
}

template<typename T>
inline auto ResourceManager::Load_Continue(const std::string& path, Xml::XMLElement* root_element)-> const std::shared_ptr<T>
{
	static_assert(std::is_base_of<IResource, T>::value, "Provided type does not implement IResource");

	if (!std::filesystem::exists(path))
	{
		assert(false);
		return nullptr;
	}

	auto last_index = path.find_last_of("\\/");
	auto file_name = path.substr(last_index + 1, path.length());
	last_index = file_name.find_last_of(".");
	auto resource_name = file_name.substr(0, last_index);

	std::shared_ptr<T> resource;

	if (HasResource(resource_name, IResource::DeduceResourceType<T>()))
		 resource = GetResourceFromName<T>(resource_name);

	resource = std::make_shared<T>(tool);
	resource->SetResourceName(resource_name);
	resource->SetResourcePath(path);

	if (!resource->LoadFromFile_Continue(root_element))
	{
		assert(false);
		return nullptr;
	}

	return resource;
}

template<typename T>
inline auto ResourceManager::GetResourceFromName(const std::string& name) -> const std::shared_ptr<T>
{
	static_assert(std::is_base_of<IResource, T>::value, "Provided type does not implement IResource");
	for (const auto& resource : resource_groups[IResource::DeduceResourceType<T>()])
	{
		if (resource->GetResourceName() == name)
			return std::static_pointer_cast<T>(resource);
	}

	return nullptr;
}

template<typename T>
inline auto ResourceManager::GetResourceFromPath(const std::string& path) -> const std::shared_ptr<T>
{
	static_assert(std::is_base_of<IResource, T>::value, "Provided type does not implement IResource");
	for (const auto& resource : resource_groups[IResource::DeduceResourceType<T>()])
	{
		if (resource->GetResourcePath() == path)
			return std::static_pointer_cast<T>(resource);
	}

	return nullptr;
}

template<typename T>
inline auto ResourceManager::RegisterResource(const std::shared_ptr<T>& resource)
{
	static_assert(std::is_base_of<IResource, T>::value, "Provided type does not implement IResource");

	if (!resource)
	{
		assert(false);
		return;
	}

	std::lock_guard<std::mutex> guard(resource_mutex);
	resource_groups[resource->GetResourceType()].emplace_back(resource);

}
