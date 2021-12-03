#pragma once
#include "ISubsystem.h"

class Context final :
	public ISubsystem
{
public:
	Context(class Tool* const tool);
	~Context() = default;

	bool Initialize() override;
	void Update() override {};

	auto GetDocument() const -> const Xml::XMLDocument& { return doc; }
	auto GetDeclaration() const -> const Xml::XMLDeclaration* { return dec; }
	
	void AddElement(const std::string& element_name, const std::string& base_element_name = "");

	template<typename T>
	bool AddAttribute(const std::string& element_name, const std::string& attribute_name, const T& value);

	auto GetElement(const std::string& element_name) -> Xml::XMLElement*;

	auto GetFileName() const -> const std::string& { return file_name; }
	auto SetFileName(const std::string& file_name){ return this->file_name = file_name; }

	bool SaveToFile(const std::string& path);
	bool LoadFromFile(const std::string& path);

private:
	Xml::XMLDocument doc;
	Xml::XMLDeclaration* dec;
	std::string file_name = "";
};


template<typename T>
inline bool Context::AddAttribute(const std::string& element_name, const std::string& attribute_name, const T& value)
{
	Xml::XMLElement* element = GetElement(element_name);
	
	if (!element)
		return false;
	
	element->SetAttribute(attribute_name.c_str(), value);
	return true;
}
