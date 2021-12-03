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
	void AddAttribute(const std::string& element_name, const std::string& attribute_name, const T& value);

	auto GetElement(const std::string& element_name) -> Xml::XMLElement*;

	bool SaveToFile(const std::string& path);
	bool LoadFromFile(const std::string& path);

private:
	Xml::XMLDocument doc;
	Xml::XMLDeclaration* dec;
};


template<typename T>
inline void Context::AddAttribute(const std::string& element_name, const std::string& attribute_name, const T& value)
{
	Xml::XMLElement* element = GetElement(element_name);
	element->SetAttribute(attribute_name, value);
}
