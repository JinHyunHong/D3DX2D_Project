#pragma once

enum class ResourceType : uint
{
	Unknown,
	Animation,
	Texture2D,
	Tile,
	Mesh,
	Material
};


class IResource
{
public:
	template<typename T>
	static constexpr ResourceType DeduceResourceType();

public:
	IResource(class Tool* const tool, const ResourceType type = ResourceType::Unknown);
	virtual ~IResource() = default;

	virtual bool SaveToFile(const std::string& path) = 0;
	virtual bool LoadFromFile(const std::string& path) = 0;
	virtual void SaveToFile_Continue(Xml::XMLDocument& doc) = 0;
	virtual void SaveToFile_Continue(Xml::XMLDocument& doc, Xml::XMLElement* root_element) = 0;
	virtual bool LoadFromFile_Continue(Xml::XMLElement* sib_element) = 0;

	auto GetResourceType() const { return resource_type; }
	auto GetResourceName() const { return resource_name; }
	auto GetResourcePath() const { return resource_path; }

	void SetResourceName(const std::string& name) { this->resource_name = name; }
	void SetResourcePath(const std::string& path) { this->resource_path = path; }

protected:
	class Tool* tool = nullptr;
	ResourceType resource_type = ResourceType::Unknown;
	std::string resource_name = "";
	std::string resource_path = "";
};